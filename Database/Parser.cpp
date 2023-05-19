#include "Parser.h"
#include "Table_functions.h"

int Parser :: _table[MAX_ROWS][MAX_COLS];

Parser :: Parser() : _fail(true)
{
    build_keyword_list();

    make_table();
}

Parser :: Parser(const string &input)
{
    build_keyword_list();

    make_table();

    set_string(input);
}

void Parser :: set_string(string input)
{
    // clear out the input queue & ptree

    while (!_input_q.empty())
    {
        _input_q.pop();
    }

    _ptree.clear();

    // convert input string to input queue

    STokenizer tokenizer(input.c_str());

    while (tokenizer.more())
    {
        StrToken st;

        tokenizer >> st;

        // accept only words, numbers, commas, dots, and stars

        if (st.type() == 1 || st.type() == 2 ||
                st.token_str() == "," || st.token_str() == "." ||
                st.token_str() == "*")
        {

            string str = st.token_str();

            // strip any quotes from words

            if (st.type() == 1 && str.front() == '"' && str.back() == '"')
            {
                str = str.substr(1, str.size() - 2);
            }

            _input_q.push(str);
        }
    }

//    queue<string> copy = _input_q;

//    while(!copy.empty())
//    {
//        cout << copy.front() << endl;

//        copy.pop();
//    }

    _fail = !get_parse_tree();
}

int Parser :: get_column(string token) const
{
    int col_num = -1;

    if (_keywords.contains(token))
    {
        col_num = _keywords[token];
    }

    else
    {
        col_num = 14; // value for symbol
    }

    return col_num;
}

bool Parser :: fail() const
{
    return _fail;
}

MultiMap<string, string> Parser :: parse_tree() const
{
    return _ptree;
}

void Parser::build_keyword_list()
{
    _keywords["CREATE"] = 1;

    _keywords["MAKE"] = 2;

    _keywords["TABLE"] = 3;

    _keywords["FIELDS"] = 4;

    _keywords[","] = 5;

    _keywords["INSERT"] = 6;

    _keywords["INTO"] = 7;

    _keywords["VALUES"] = 8;

    _keywords["SELECT"] = 9;

    _keywords["*"] = 10;

    _keywords["FROM"] = 11;

    _keywords["WHERE"] = 12;

    _keywords["DROP"] = 13;

    // col 14 is reserved for sym

    _keywords["BATCH"] = 15;

    _keywords["."] = 16;
}

void Parser :: make_table()
{
    init_table(_table);

    // add rules for my state machines

    // Create/Make command

    mark_cells(0, _table, 1, 2, 1); // Begins with "CREATE" or "MAKE"

    mark_cell(1, _table, 3, 2);     // followed by "TABLE

    mark_cell(2, _table, 14, 3);    // followed by table name sym

    mark_cell(3, _table, 4, 4);     // followed by "FIELDS"

    mark_cell(4, _table, 14, 5);    // followed by field name sym

    mark_cell(5, _table, 5, 6);     // followed, optionally, by a ","

    mark_cell(6, _table, 14, 5);    // followed by additional field name sym

    for (int i = 0; i <= 6; i++)
    {
        mark_fail(_table, i);
    }

    mark_success(_table, 5);

    // Insert command

    mark_cell(10, _table, 6, 11);  // Begins with "INSERT"

    mark_cell(11, _table, 7, 12);  // followed by "INTO"

    mark_cell(12, _table, 14, 13); // followed by table name

    mark_cell(13, _table, 8, 14);  // followed by "VALUES"

    mark_cell(14, _table, 14, 15); // followed by some value

    mark_cell(15, _table, 5, 16);  // followed by ","

    mark_cell(16, _table, 14, 15); // followed by additional values

    for (int i = 10; i <= 16; i++)
    {
        mark_fail(_table, i);
    }

    mark_success(_table, 15);


    // Drop command

    mark_cell(30, _table, 13, 31); // Begins with "DROP"

    mark_cell(31, _table, 3, 32);  // followed by "TABLE"

    mark_cell(32, _table, 14, 33); // followed by "TABLE"

    for (int i = 30; i < 33; i++)
    {
        mark_fail(_table, i);
    }

    mark_success(_table, 33);


    // Select command

    mark_cell(20, _table, 9, 21);  // Begins with "SELECT"

    mark_cell(21, _table, 10, 22); // followed by "*" OR

    mark_cell(21, _table, 14, 23); // followed by field name

    mark_cell(21, _table, 10, 22); // followed by "*" OR

    mark_cell(22, _table, 11, 25); // followed by "FROM"

    mark_cell(23, _table, 5, 24);  // followed by ","

    mark_cell(23, _table, 11, 25); // followed by "FROM"

    mark_cell(24, _table, 14, 23); // followed by additional field names

    mark_cell(25, _table, 14, 26); // followed by table name

    mark_cell(26, _table, 12, 27); // followed by "WHERE"

    mark_cell(27, _table, 14, 28); // followed by first word of Conditions

    mark_cell(28, _table, 14, 28); // followed by rest of words of Conditions

    for (int i = 20; i <= 28; i++)
    {
        mark_fail(_table, i);
    }

    mark_success(_table, 26);

    mark_success(_table, 28);

    // Batch command

    mark_cell(35, _table, 15, 36); // Begins with "BATCH"

    mark_cell(36, _table, 14, 37); // followed by file name

    mark_cell(37, _table, 16, 38); // followed by "."

    mark_cell(38, _table, 14, 39); // followed by file extension

    for (int i = 35; i <= 39; i++)
    {
        mark_fail(_table, i);
    }

    mark_success(_table, 39);
}

bool Parser :: passes_state_machine(int start_state)
{
    queue<string> input_copy = _input_q;


    int current_state = start_state;

    string current_token;


    while (!input_copy.empty() && current_state != -1)
    {
        // move to the next state

        current_token = uppercase(input_copy.front());

        input_copy.pop();

        current_state = _table[current_state][get_column(current_token)];
    }

    return current_state != -1 && _table[current_state][0];
}

string Parser :: uppercase(string str)
{
    for (int i = 0; i < str.size(); i++)
    {
        str[i] = toupper(str[i]);
    }

    return str;
}

void Parser :: extract_select_command()
{
    _ptree["Command"] += uppercase(_input_q.front());

    _input_q.pop();


    // read all field values

    while (uppercase(_input_q.front()) != "FROM")
    {
        if (_input_q.front() != ",")
        {
            _ptree["Fields"] += _input_q.front();
        }

        _input_q.pop();
    }

    _input_q.pop(); // remove "from" keyword


    _ptree["Table"] += _input_q.front();

    _input_q.pop();


    if (!_input_q.empty())
    {
        _ptree["Where"] += string("yes");

        _input_q.pop(); // remove "where" keyword

        // remaining strings are conditions

        while (!_input_q.empty())
        {
            _ptree["Condition"] += _input_q.front();

            _input_q.pop();
        }
    }

    else
    {
        _ptree["Where"] += string("no");
    }
}

bool Parser :: get_parse_tree()
{
    if (passes_state_machine(0)) // Create/Make table command
    {
        _ptree["Command"] += uppercase(_input_q.front());

        _input_q.pop();


        _input_q.pop(); // remove "table" keyword


        _ptree["Table"] += _input_q.front();

        _input_q.pop();


        _input_q.pop(); // remove "fields" keyword


        // remainder of command are the fields

        while (!_input_q.empty())
        {
            if (_input_q.front() != ",")
            {
                _ptree["Fields"] += _input_q.front();
            }

            _input_q.pop();
        }

        return true;
    }

    else if (passes_state_machine(10)) // Insert command
    {
        _ptree["Command"] += uppercase(_input_q.front());

        _input_q.pop();

        _input_q.pop(); // remove "into" keyword


        _ptree["Table"] += _input_q.front();

        _input_q.pop();


        _input_q.pop(); // remove "values" keyword


        // remainder of command are the values

        while (!_input_q.empty())
        {
            if (_input_q.front() != ",")
            {
                _ptree["Values"] += _input_q.front();
            }

            _input_q.pop();
        }

        return true;
    }

    else if (passes_state_machine(20))
    {
        extract_select_command();

        return true;
    }

    else if (passes_state_machine(30)) // Drop table command
    {
        _ptree["Command"] += uppercase(_input_q.front());

        _input_q.pop();


        _input_q.pop(); // remove table keyword


        _ptree["Table"] += _input_q.front();

        _input_q.pop();

        return true;
    }

    else if (passes_state_machine(35)) // Batch command
    {
        _ptree["Command"] += uppercase(_input_q.front());

        _input_q.pop();


        _ptree["Filename"] += _input_q.front();

        _input_q.pop();


        _input_q.pop(); // remove dot


        _ptree["Extension"] += _input_q.front();

        _input_q.pop();

        return true;
    }

    else
    {
        _ptree.clear();

        return false;
    }
}
