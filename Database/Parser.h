#ifndef PARSER_H
#define PARSER_H

#include <string>

#include "Queue.h"

#include "MultiMap.h"
#include "Map.h"
#include "STokenizer.h"

#include <queue>

using namespace std;

class Parser
{
    private:

        static const int MAX_ROWS = 40;

        static const int MAX_COLS = 256;


        int get_column(string token) const;

        bool get_parse_tree();

        void build_keyword_list();

        void make_table();

        bool passes_state_machine(int start_state);

        string uppercase(string str);

        void extract_select_command();


        Map<string, int> _keywords;

        queue<string> _input_q;

        bool _fail;

        MultiMap<string, string> _ptree;


        static int _table[MAX_ROWS][MAX_COLS];

    public:

        Parser();

        Parser(const string &input);


        void set_string(string input);

        bool fail() const;

        MultiMap<string, string> parse_tree() const;
};

#endif
