#ifndef STOKENIZER_H
#define STOKENIZER_H

#include <string>

#include "StrToken.h"

using namespace std;

class STokenizer
{
    private:

        static const int MAX_BUFFER = 201;

        static const int MAX_ROWS = 40;

        static const int MAX_COLUMNS = 256;


        void make_table(int _table[][MAX_COLUMNS]); //sets table to recognize values we determine

        bool get_token(int start_state, string &token); //will traverse the string and find the first valid token

        char buffer[MAX_BUFFER]; // the string/sentence

        int _pos; // position in the string/sentence

        static int _table[MAX_ROWS][MAX_COLUMNS]; //the table

    public:

        STokenizer(); //Default Constructor

        STokenizer(const char str[]); //Initialized Constructor

        bool done(); // Position is at the end and there are no more tokens

        bool more(); // Position is somewhere in string and there are more tokens

        friend STokenizer &operator>>(STokenizer &s, StrToken &t); //get_token

        void set_string(const char str[]); //takes a string/sentence
};

#endif
