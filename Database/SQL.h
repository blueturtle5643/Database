#ifndef SQL_H
#define SQL_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Map.h"
#include "Parser.h"
#include "Table.h"

using namespace std;

class SQL
{
    private:

        void run_command(string command_str);

        void insert();

        void select();

        void create_table();

        void drop_table();

        void process_batch(string filename);


        Map<string, Table> _tables;

        Parser _parser;

        vector<string> _table_names;

        int cmd_num;

    public:

        SQL();

        void run();
};

SQL :: SQL() : cmd_num(-2)
{

}

void SQL :: run()
{
    // print intro message

    cout << "\nWelcome to SQL. Enter your command: " << endl;

    cout << "> ";

    string input;

    getline(cin, input);

    while (input != "exit")
    {
        run_command(input);

        cout << "\n> ";

        getline(cin, input);
    }
}

void SQL :: run_command(string command_str)
{
    ++cmd_num;

    _parser.set_string(command_str);

    if (_parser.fail())
    {
        // print error message

        cout << '[' << cmd_num << "]: "
             << "Cannot process the following command: \n";
        cout << '\t' << command_str << endl;
    }

    else
    {
        // print out command

        cout << endl << '[' << cmd_num << "]: " << command_str << endl << endl;

        //bob

        MultiMap<string, string> ptree = _parser.parse_tree();

        //cout << ptree << endl;

        string cmd = ptree["Command"].front();

        if (cmd == "CREATE" || cmd == "MAKE")
        {
            create_table();
        }

        else if (cmd == "INSERT")
        {
            insert();
        }

        else if (cmd == "SELECT")
        {
            select();
        }

        else if (cmd == "DROP")
        {
            drop_table();
        }

        else if (cmd == "BATCH")
        {
            string filename = ptree["Filename"].front();

            string extension = ptree["Extension"].front();

            process_batch(filename + string(".") + extension);
        }

        cout << "\nSQL: DONE." << endl << endl << endl;
    }
}

void SQL :: insert()
{
    //bob

    MultiMap<string, string> ptree = _parser.parse_tree();

    string table_name = ptree["Table"].front();

    if (_tables.contains(table_name))
    {
        _tables[table_name].insert_into(ptree["Values"]);

        cout << "\nSQL::run: inserted." << endl;
    }

    else
    {
        cout << "\nInsert unsuccessful,  \"" << table_name <<
                "\" does not exist." << endl;
    }
}

void SQL :: select()
{
    //bob

    MultiMap<string, string> ptree = _parser.parse_tree();

    string table_name = ptree["Table"].front();

    if (_tables.contains(table_name))
    {
        //bob

        vector<string> fields = ptree["Fields"];

        if (fields.size() == 1 && fields.front() == "*")
        {
            fields = _tables[table_name].get_fields();
        }

//        cout << ptree << endl;

        if (ptree["Where"].front() == "yes")
        {
            //bob

            vector<string> conditions = ptree["Condition"];

            //bob

            // test a function to see if there's an error matching.

            try
            {
                //bob

                Table results = _tables[table_name].select(fields, conditions);

                results.print();
            }

            catch (invalid_argument &e)
            {
                cout << "Unable to process this command: " << e.what();
            }

            //bob

//            Table results = _tables[table_name].select(fields, conditions);

//            results.print();
        }

        else
        {
            //bob

            Table results = _tables[table_name].select(fields);

            results.print();
        }
    }
    else
    {
        cout << "\nSelect unsuccessful,  \"" << table_name <<
                "\" does not exist." << endl;
    }
}

void SQL :: create_table()
{
    //bob

    MultiMap<string, string> ptree = _parser.parse_tree();


    string table_name = ptree["Table"].front();

    vector<string> fields = ptree["Fields"];


    // create table

    Table table(table_name, fields);


    // add table to SQL variables

    _table_names.push_back(table_name);

    _tables.insert(table_name, table);
}

void SQL :: drop_table()
{
    //bob

    MultiMap<string, string> ptree = _parser.parse_tree();

    string table_name = ptree["Table"].front();

    if (_tables.contains(table_name))
    {
        _tables.erase(table_name);

        cout << "\nDrop for \"" << table_name << "\" was successful." << endl;
    }

    else
    {
        cout << "\nDrop unsuccessful,  \"" << table_name <<
                "\" does not exist." << endl;
    }
}

void SQL :: process_batch(string filename)
{
    ifstream batchFile(filename);

    if (batchFile.fail())
    {
        cout << "\nBatch process unsuccessful. Could not open \""
             << filename << "\"." << endl;
    }

    else
    {
        string line;

        getline(batchFile, line);

        while (!batchFile.eof())
        {
            if (line.size() >= 2 && line[0] != '/' && line[1] != '/')
            {
                run_command(line);
            }

            else if((line[0] == '/' && line[1] == '/') || line[0] == '-')
            {
                cout << endl << line << endl;
            }

            getline(batchFile, line);
        }
    }
}

#endif
