/*********************************************************
* AUTHOR : Brian Ouyang
* PROJECT: Assignment # 20 : Chapter
* CLASS : CS 8
* SECTION : MTH: 1:00p – 3:05p
* Due Date : 12/5/20
*********************************************************/
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <assert.h>
#include "SQL.h"
using namespace std;
/**********************************************************
*
* Programming Project: Final Project: Database
*_________________________________________________________
* Final project combines file storage, multiple B+Trees as
* data structures, finite state machines to parse a
* command and display/store a table(collection of records)
*_________________________________________________________
*
*  INPUT:
*
* Basic SQL commands, most notably batch which can
* test multiple commands
*
* OUTPUT:
*
* Desired output, some commands will be printed.
*
* PROCESSING:
*
* Program processes strings and uses finite state machines
* to break down the string into a command and acts on the
* command.
*
***********************************************************/
// functions

void parser_side_tests();

void test_iter_for_MMap_copy();

void parser_access_tests();

template <typename T>
void menu();

int main()
{
    char option;

    do
    {
        srand(time(0));

        menu<int>();

        cout << "\nDo you want to repeat the calculation? Enter 'Y' or 'y': ";

        cin >> option;
    }
    while (option == 'y' || option == 'Y');

    return 0;
}
/**********************************************************
*
*
* Do you want to repeat the calculation? Enter 'Y' or 'y':
*
***********************************************************/

template <typename T>
void menu()
{
    //parser_side_tests();

    //test_iter_for_MMap_copy();

    //parser_access_tests();


    SQL sql;

    sql.run();
}

void parser_side_tests()
{
    Parser p;

//    p.set_string("drop table names");
//    p.set_string("create table names fields first, last");
//    p.set_string("insert into names values john, smith");
//    p.set_string("select * from names where adfkaldfkj");

    p.set_string("insert into employee values \"Van Gogh\",	\"Jim Bob\", 	"
                 "	\"Phys Ed\"");

    //bob

    vector<string> values = p.parse_tree()["Values"];


    //bob

    for(int i = 0; i < values.size(); i++)
    {
        string value = values[i];

        cout << value << endl;
    }
}

void test_iter_for_MMap_copy()
{
    MultiMap<int, int> original;

    for (int i = 0; i < 6; i++)
    {
        original.insert(i, i);
    }

    //bob

    MultiMap<int, int> copy = original;

    // print original using iter

    cout << "\nPrinting original: " << endl;

    //bob

    for (MultiMap<int,int> :: Iterator it = original.begin(); it !=
         original.end(); it++)
    {
        cout << (*it).key << endl;
    }

    // print copy using iter

    cout << "\n\nPrinting copy\n";

    //bob

    for (MultiMap<int,int> :: Iterator it = copy.begin();
         it != copy.end(); it++)
    {
        cout << (*it).key << endl;
    }
}

void parser_access_tests()
{
    Parser parser;

    parser.set_string("select * from student where lname > Yang");

    MultiMap<string, string> ptree = parser.parse_tree();

    //bob

    vector<string> values = ptree["Condition"];

    cout << "\nDone." << endl;
}

