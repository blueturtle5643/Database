#include <cstring>

#include "STokenizer.h"
#include "Table_functions.h"

int STokenizer :: _table[MAX_ROWS][MAX_COLUMNS];

void STokenizer :: make_table(int _table[][MAX_COLUMNS])
{
    init_table(_table);

    // add rules for my state machines

    // Alphanumeric word

    mark_cells(0, _table, 65, 90, 1);  // initial uppercase letter or...

    mark_cells(0, _table, 97, 122, 1); // initial lowercase letter

    mark_cells(1, _table, 65, 90, 1);  // additional uppercase letters or...

    mark_cells(1, _table, 97, 122, 1); // additional lowercase letters or...

    mark_cells(1, _table, 48, 57, 1);  // additional number/s or...

    mark_cell(1, _table, 39, 2);       // apostrophe

    mark_cells(2, _table, 65, 90, 2);  // additional uppercase letters or...

    mark_cells(2, _table, 97, 122, 2); // additional lowercase letters or...

    mark_cells(2, _table, 48, 57, 2);  // additional number/s or...

    mark_fail(_table, 0);

    mark_success(_table, 1);

    mark_success(_table, 2);


    // Punctuation

    const char punctuation[] = ".,\"':;?!*";

    mark_cells(3, _table, punctuation, 4);

    mark_fail(_table, 3);

    mark_success(_table, 4);


    // Whitespace

    const char whitespace[] = " \r\n\t";

    mark_cells(5, _table, whitespace, 6);

    mark_fail(_table, 5);

    mark_success(_table, 6);


    // Numbers

    mark_cells(10, _table, 48, 57, 11); // initial digit

    mark_cell(10, _table, 46, 19);      // initial decimal point

    mark_cells(11, _table, 48, 57, 12); // initial 2 digits

    mark_cell(11, _table, 46, 19);      // decimal follows single digit

    mark_cell(11, _table, 44, 14);      // single digit with comma

    mark_cells(12, _table, 48, 57, 13); // initial 3 digits

    mark_cell(12, _table, 46, 19);      // decimal follows 2 digits

    mark_cell(12, _table, 44, 14);      // 2 digits with comma

    mark_cells(13, _table, 48, 57, 18); // more than 3 digits

    mark_cell(13, _table, 46, 19);      // decimal follows 3 digits

    mark_cell(13, _table, 44, 14);      // 3 digits with comma

    mark_cells(14, _table, 48, 57, 15); // first digit after comma

    mark_cells(15, _table, 48, 57, 16); // second digit after comma

    mark_cells(16, _table, 48, 57, 17); // third digit after comma

    mark_cell(17, _table, 46, 19);      // decimal follows last 3 digits

    mark_cell(17, _table, 44, 14);      // additional commas

    mark_cells(18, _table, 48, 57, 18); // more than 4 digits before decimal

    mark_cell(18, _table, 46, 19);      // decimal follows large sequence of digits

    mark_cells(19, _table, 48, 57, 20); // first digit after decimal

    mark_cells(20, _table, 48, 57, 20); // additional digits after decimal

    mark_fail(_table, 10);

    mark_fail(_table, 14);

    mark_fail(_table, 15);

    mark_fail(_table, 16);

    mark_fail(_table, 19);

    mark_success(_table, 11);

    mark_success(_table, 12);

    mark_success(_table, 13);

    mark_success(_table, 17);

    mark_success(_table, 18);

    mark_success(_table, 20);


    // String in quotes (extension to alphanumeric token)

    mark_cell(0, _table, 34, 26);       // initial quote mark

    mark_cells(26, _table, 32, 33, 27); // any character after quote, except another quote

    mark_cells(26, _table, 35, 126, 27);

    mark_cells(27, _table, 32, 33, 27); // additional non-quote characters

    mark_cells(27, _table, 35, 126, 27);

    mark_cell(27, _table, 34, 28); // final quote mark

    mark_fail(_table, 26);

    mark_fail(_table, 27);

    mark_success(_table, 28);


    // Relational symbols (extension to alphanumeric token)

    mark_cell(0, _table, 60, 29);  // "<" symbol

    mark_cell(0, _table, 62, 30);  // ">" symbol

    mark_cell(0, _table, 61, 31);  // "=" symbol

    mark_cell(29, _table, 61, 32); // "<=" symbol

    mark_cell(30, _table, 61, 33); // ">=" symbol

    mark_success(_table, 29);

    mark_success(_table, 30);

    mark_success(_table, 31);

    mark_success(_table, 32);

    mark_success(_table, 33);
}

bool STokenizer :: get_token(int start_state, string &token)
{
    const int BUFFER_LENGTH = strlen(buffer);


    int current_position = _pos;

    int last_successful_state_pos = _pos - 1;

    int current_state = start_state;

    int last_success_state = start_state;


    char next_input_character = buffer[current_position];

    int next_state = _table[current_state][next_input_character];

    while (next_state != -1)
    {
        current_state = next_state;

        if (_table[current_state][0])
        {
            // copy set of characters since last successful state

            token.append(buffer + last_successful_state_pos + 1, buffer +
                         current_position + 1);


            last_success_state = current_state;

            last_successful_state_pos = current_position;
        }

        current_position++;

        if (current_position < BUFFER_LENGTH)
        {
            next_input_character = buffer[current_position];

            next_state = _table[current_state][next_input_character];
        }

        else
        {
            next_state = -1;
        }
    }

    return _table[last_success_state][0];
}

STokenizer :: STokenizer() : _pos(0)
{
    for (int i = 0; i < MAX_BUFFER; i++)
    {
        buffer[i] = '\0';
    }

    make_table(_table);
}

STokenizer :: STokenizer(const char str[]) : _pos(0)
{
    set_string(str);

    make_table(_table);
}

bool STokenizer :: done()
{
    return buffer[_pos] == '\0';
}

bool STokenizer :: more()
{
    return !done();
}

STokenizer &operator >>(STokenizer &s, StrToken &t)
{
    string token_str;

    int token_type = 0;

    if (s.get_token(0, token_str))
    {
        // determine type of StrToken and assign to t (Parsing stage on 'token_str')

        token_type = 1;
    }

    else if (s.get_token(10, token_str))
    {
        token_type = 2;
    }

    else if (s.get_token(3, token_str))
    {
        token_type = 3;
    }

    else if (s.get_token(5, token_str))
    {
        token_type = 4;
    }

    else
    {
        token_str = s.buffer[s._pos];
    }

    s._pos += token_str.length();

    t = StrToken(token_str, token_type);

    return s;
}

void STokenizer :: set_string(const char str[])
{
    int input_string_length = strlen(str);

    if (input_string_length < (MAX_BUFFER - 1))
    {
        strncpy(buffer, str, input_string_length);

        buffer[input_string_length] = '\0';
    }

    else
    {
        strncpy(buffer, str, MAX_BUFFER - 1);

        buffer[MAX_BUFFER] = '\0';
    }
    _pos = 0;
}
