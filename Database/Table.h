#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "Record.h"
#include "MultiMap.h"
#include "Map.h"

#include "Token.h"
#include "ShuntingYard.h"
#include "RPN.h"

#include "ConditionalToken.h"
#include "Field.h"
#include "Value.h"
#include "Relational.h"
#include "Logical.h"
#include "LParenthesis.h"
#include "RParenthesis.h"

#include "Stack.h"

using namespace std;

typedef vector<string> vectorstr;

typedef string field;

typedef string value;

typedef long rec_no;

typedef long order;


class Table
{
    private:

        string _table_name;

        Map<field, MultiMap<value, rec_no>> _indices;

        vectorstr _field_names;

        Map<field, order> _field_map;

        int _serial_num;

        int last_record_number;

        bool empty;

        void reindex(fstream &ins);

        vector<ConditionalToken *> Tokenize(const vector<string> &conditionals);

        bool conditionals_validated(const vector<string> &conditionals);

        bool is_value(const string &str);

        bool parenthesis_validated(const vector<string> &conditionals);

        int get_precedence(const string &str);

        string uppercase(string str);

    public:

        Table();

        Table(const string &name, const vectorstr fields);

        //name is the name of the table, fields is the strings that can
        //comprise of a single record and the cstr will create a record/table
        //row with the fields

        Table(const string &name); //if table exists, open it

        void insert_into(vectorstr field_values); //give it entire record
                                                  //worth of information

        //EX: BOB
        //EX: SMITH
        //EX: CS

        //stored as strings

        Table select(const vector<field> &fields, const vector<string>
                     &conditions);

        Table select(const vector<field> &fields);

        //field_name, an operator, specific value

        //way to use: lastname, =, Jones

        //returns every record with jones

        Table select_all(); //gives entire table?

        void set_fields(vectorstr field_names);

        vectorstr get_fields() const;

        bool is_empty() const;

        void print();
};

Table :: Table()
{

}

Table :: Table(const string &table_name, const vectorstr fields)
    : _table_name(table_name), last_record_number(-1), empty(true),
      _serial_num(0)
{
    _serial_num++;


    // set field names

    set_fields(fields);


    // create empty bin file

    fstream binFile;

    string filename = table_name + string(".bin");

    open_fileW(binFile, filename.c_str());



    // write_info: write the names of fields to text file

    ofstream txtFile(table_name + string(".txt"));

    for (int i = 0; i < fields.size(); i++)
    {
        txtFile << fields[i] << endl;
    }


    // build index structure & lookup map

    for (int i = 0; i < fields.size(); i++)
    {
        field current_field = fields[i];


        _field_map[current_field] = i;

        _indices.insert(current_field, MultiMap<value, rec_no>());
    }

//    cout << _field_map << endl;

//    cout << "\nMmap " << endl;

//    cout << _indices << endl;
}

Table :: Table(const string &table_name)
    : _table_name(table_name), last_record_number(-1), empty(false),
      _serial_num(0)
{

    // open filestream

    fstream binFile;

    string filename = table_name + string(".bin");

    open_fileRW(binFile, filename.c_str());



    // read_info: read field names from text file

    fstream txtFile;

    Record rec;

    rec.read(txtFile, 0);


    // set field names

    set_fields(rec.get_record());


    // build index structure & lookup map

    for (int i = 0; i < _field_names.size(); i++)
    {
        field current_field = _field_names[i];


        _field_map[current_field] = i;

        _indices.insert(current_field, MultiMap<value, rec_no>());
    }

    reindex(binFile);
}

void Table :: print()
{
    // print only labels for empty table

    if (last_record_number == -1)
    {
        cout << setw(10) << "record";

        for (int i = 0; i < _field_names.size(); i++)
        {
            cout << setw(16) << _field_names[i];
        }

        cout << "\n\n";

        return;
    }

    const int COLS = _field_names.size() + 1;    // account for "record no." column

    const int ROWS = last_record_number + 1 + 1; // account for zero-based index & top row of labels


    // print table, fill values into 2D vector

    vector<string> emptyRow(COLS);

    vector<vector<string>> table_str_values(ROWS, emptyRow);


    // fill top row of labels

    table_str_values[0][0] = "record";

    for (int i = 0; i < _field_names.size(); i++)
    {
        table_str_values[0][i + 1] = _field_names[i];
    }


    // fill record numbers

    for (int i = 0; i <= last_record_number; i++)
    {
        table_str_values[i + 1][0] = to_string(i);
    }

    //bob

    for (Map<string, MultiMap<string, long>> ::Iterator
         field_it = _indices.begin(); field_it != _indices.end();
                  field_it++)
    {
        //bob

        string corresponding_field = (*field_it).key;

        //bob

        long corresponding_field_index = _field_map[corresponding_field];

        //bob

        MultiMap<string, long> corresponding_mmap = (*field_it).value;

        //bob
        for (MultiMap <string,long> :: Iterator value_it =
             corresponding_mmap.begin();
                          value_it != corresponding_mmap.end();
                          value_it++)
        {
            //bob

            vector<long> corresponding_rec_nums = (*value_it).values;

            //bob

            string value_str = (*value_it).key;

            for (int i = 0; i < corresponding_rec_nums.size(); i++)
            {
                const int row = corresponding_rec_nums[i] + 1;

                const int col = corresponding_field_index + 1;

                table_str_values[row][col] = value_str;
            }
        }
    }

    // finally, print 2D vector


    // print top row

    cout << setw(10) << table_str_values[0][0];

    for (int i = 0; i < _field_names.size(); i++)
    {
        cout << setw(16) << _field_names[i];
    }

    cout << "\n\n-----------------------------------------------------------"
            "-------------------------------------------------------------" <<
            endl;


    // print all values

    for (int i = 1; i < ROWS; i++)
    {
        cout << setw(10) << table_str_values[i][0];

        for (int j = 1; j < COLS; j++)
        {
            cout << setw(16) << table_str_values[i][j];
        }

        cout << endl;
    }

    cout << endl;
}

Table Table :: select_all()
{
    const int COLS = _field_names.size() + 1;    // account for "record no." column

    const int ROWS = last_record_number + 1 + 1; // account for zero-based index & top row of labels


    // print table, fill values into 2D vector

    vector<string> emptyRow(COLS);

    vector<vector<string>> table_str_values(ROWS);

    // fill top row of labels

    table_str_values[0][0] = "record";

    for (int i = 0; i < _field_names.size(); i++)
    {
        table_str_values[0][i + 1] = _field_names[i];
    }

    //bob

    for (Map<string, MultiMap<string, long>> ::Iterator field_it =
         _indices.begin(); field_it != _indices.end(); field_it++)
    {
        //bob

        string corresponding_field = (*field_it).key;

        //bob

        long corresponding_field_index = _field_map[corresponding_field];

        //bob

        for (MultiMap<string, long> ::Iterator value_it = (*field_it).
             value.begin();
             value_it != (*field_it).value.end();
             value_it++)
        {
            //bob

            vector<long> corresponding_rec_nums = (*value_it).values;

            //bob

            string value_str = (*value_it).key;

            for (int i = 0; i < corresponding_rec_nums.size(); i++)
            {
                const int row = corresponding_rec_nums[i] + 1;

                const int col = corresponding_field_index + 1;

                table_str_values[row][col] = value_str;
            }
        }
    }

    // finally, print 2D vector


    // print top row

    cout << setw(10) << table_str_values[0][0];

    for (int i = 0; i < _field_names.size(); i++)
    {
        cout << setw(16) << _field_names[i];
    }

    cout << "\n\n";


    // print all values

    for (int i = 1; i < ROWS; i++)
    {
        cout << setw(10) << table_str_values[i][0];

        for (int j = 1; j < COLS; j++)
        {
            cout << setw(16) << table_str_values[i][j];
        }

        cout << endl;
    }

    return *this;
}

void Table :: insert_into(vectorstr field_values)
{
    empty = false;

    // file already exists, open it to insert into

    fstream existingBinFile;

    string filename = _table_name + string(".bin");

    open_fileRW(existingBinFile, filename.c_str());


    // write field_values into the existing binary file

    Record rec(field_values); //filling the envelop

    long record_num = rec.write(existingBinFile);

    existingBinFile.close();


    // inserting each value into index structure

    for (int i = 0; i < field_values.size(); i++)
    {
        //bob

        string current_field = _field_names[i];

        //bob

        string current_value = field_values[i];

        //bob

        MultiMap<string, long> &current_multimap = _indices[current_field];

        current_multimap[current_value] += record_num;
    }

    last_record_number = record_num;
}

void Table :: reindex(fstream &ins)
{
    Record rec;

    long recno = 0;

    while (!ins.eof())
    {
        rec.read(ins, recno);

        vectorstr values = rec.get_record();

        for (int i = 0; i < values.size(); i++)
        {
            field current_field = _field_names[i];

            value current_value = values[i];


            _indices[current_field][current_value] += recno;
        }

        recno++;

        last_record_number++;
    }
}

void Table :: set_fields(vectorstr field_names)
{
    _field_names = field_names;
}

vectorstr Table :: get_fields() const
{
    return _field_names;
}

bool Table :: is_empty() const
{
    return empty;
}

bool Table :: parenthesis_validated(const vector<string> &conditionals)
{
    //LOGIC: iterates through the vector of conditionals, storing every
    //parentheses in a stack of strings.

    stack<string> parenths;

    for (int i = 0; i < conditionals.size(); i++)
    {
        string str = conditionals[i];

        if (str == "(")
        {
            parenths.push(str);
        }

        else if (str == ")")
        {
            if (parenths.empty())
            {
                return false;
            }

            else
            {
                parenths.pop();
            }
        }
    }

    return true;
}

bool Table :: is_value(const string &str)
{
    // a value is something that is not a field, relational, or logical string

    return (!_field_map.contains(str) &&
           str != "<" && str != "<=" && str != ">" && str != ">=" &&
            str != "=" && str != "AND" && str != "OR" && str
            != "(" && str != ")");
}

bool Table :: conditionals_validated(const vector<string> &conditionals)
{
//    if (!parenthesis_validated(conditionals))
//    {
//        return false;
//    }

    //all conditional statements should be 3 tokens EX: a > b

    if (!parenthesis_validated(conditionals) || conditionals.size() < 3)
    {
        return false;
    }

    for (int i = 0; i < conditionals.size(); i++)
    {
        string str = conditionals[i];


        bool str_is_relational = str == "<" || str == "<=" || str == ">"
                || str == ">=" || str == "=";

        bool str_is_logical = str == "AND" || str == "OR";


        string left_str, right_str;


        bool has_left_string = (i - 1) >= 0;

        if (has_left_string)
        {
            left_str = conditionals[i - 1];
        }

        bool has_right_string = i + 1 < conditionals.size();

        if (has_right_string)
        {
            right_str = conditionals[i + 1];
        }


        // every relational has to have a field on the left

        if (str_is_relational)
        {
            if (!has_left_string || (has_left_string &&
                                     !_field_map.contains(left_str)))
            {
                return false;
            }
        }

        if (str_is_logical)
        {
            // every logical must have a ")" or a value on the left

            if (!has_left_string ||
                (has_left_string && (left_str != ")" || !is_value(str))))
            {
                return false;
            }


            // every logical must have a "(" or a field on the right

            if (!has_right_string ||
                (has_right_string && (right_str
                                      != "(" || !_field_map.contains(str))))
            {
                return false;
            }
        }
    }

    return true;
}

int Table :: get_precedence(const string &str)
{
    int precedence;

    if (str == "<" || str == "<=" || str == ">" || str == ">=")
    {
        precedence = 4;
    }

    else if (str == "=")
    {
        precedence = 3;
    }

    else if (str == "AND")
    {
        precedence = 2;
    }

    else
    {
        precedence = 1;
    }

    return precedence;
}

vector<ConditionalToken *> Table ::
Tokenize(const vector<string> &conditionals)
{
    vector<ConditionalToken *> tokens;

    for (int i = 0; i < conditionals.size(); i++)
    {
        string str = conditionals[i];

        if (str == "<" || str == "<=" || str == ">" || str == ">=" ||
                str == "=")
        {
            tokens.push_back(new Field(conditionals[i - 1]));

            tokens.push_back(new Relational(str, get_precedence(str)));

            tokens.push_back(new Value(conditionals[i + 1]));
        }

        else if (uppercase(str) == "AND" || uppercase(str) == "OR")
        {
            string operand_str = uppercase(str);

            int precedence;

            if(operand_str == "AND")
            {
                precedence = 2;
            }

            else
            {
                precedence = 1;
            }

            tokens.push_back(new Logical(operand_str, precedence));

            //tokens.push_back(new Logical(uppercase(str),
                      // uppercase(str) == "AND" ? 2 : 1));
        }

        else if (str == "(")
        {
            tokens.push_back(new LParenthesis);
        }

        else if (str == ")")
        {
            tokens.push_back(new RParenthesis);
        }
    }

    return tokens;
}

Table Table :: select(const vector<field> &fields,
                      const vector<string> &conditions)
{
    if (!conditionals_validated(conditions))
    {
        throw invalid_argument("\nConditionals for select are invalid."
                                      "\n");
    }

    // Convert condition strings into tokens

    vector<ConditionalToken *> tokens = Tokenize(conditions);

    // use Shunting Yard to rearrange conditions

    ShuntingYard sy(tokens);

    queue<ConditionalToken *> postfix_tokens = sy.postfix();

    // get selected records

    RPN rpn;

    Records selected_records = rpn(_indices, postfix_tokens);

    //bob

    vector<long> record_numbers = selected_records.get_records();

    // create table from selected records by:
    //      1. reading a record from existing file
    //      2. create filtered record containing select values
    //      3. insert filtered record into results table

    // open existing file

    string existingFilename = _table_name + string(".bin");

    fstream existingFile;

    open_fileRW(existingFile, existingFilename.c_str());



    // generate results table
    string results_table_name = _table_name + string("_select");

    Table results(results_table_name, fields);

    Record existingRecord;

    //bob

    for (int i = 0; i < record_numbers.size(); i++)
    {
        long rec_no = record_numbers[i];

        existingRecord.read(existingFile, rec_no);

        //bob

        vector <string> values = existingRecord.get_record();


        vector<value> filtered_values;

        //bob

        for (int i = 0; i < fields.size(); i++)
        {
            string field = fields[i];

            //bob

            //string field;

            long corresponding_field_index = _field_map[field];

            filtered_values.push_back(values[corresponding_field_index]);
        }

        results.insert_into(filtered_values);
    }

    return results;
}

string Table :: uppercase(string str)
{
    for (int i = 0; i < str.size(); i++)
    {
        str[i] = toupper(str[i]);
    }

    return str;
}

Table Table :: select(const vector<field> &fields)
{
    string temp_name = string("temp_") + _table_name + to_string(_serial_num);

    _serial_num++;


    // open filestream

    fstream existing_binFile;

    string existing_filename = _table_name + string(".bin");

    open_fileRW(existing_binFile, existing_filename.c_str());


    // read all current records, filter it, write to temp (similar to reindex)

    Table temp_table(temp_name, fields);

    Record rec;

    long recno = 0;

    rec.read(existing_binFile, recno);

    while (!existing_binFile.eof())
    {
        vectorstr values = rec.get_record();


        // filter out values according to fields

        vectorstr filtered_values;

        if (values.size() == fields.size())
        {
            filtered_values = values;
        }

        else
        {
            for (int i = 0; i < fields.size(); i++)
            {
                field current_field = fields[i];

                order corresponding_index = _field_map[current_field];

                filtered_values.push_back(values[corresponding_index]);
            }
        }

        temp_table.insert_into(filtered_values);

        recno++;

        rec.read(existing_binFile, recno);
    }

    return temp_table;
}

#endif // TABLE_H
