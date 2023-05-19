#include "StrToken.h"

StrToken :: StrToken() : _token(), _type()
{

}

StrToken :: StrToken(string str, int type) : _token(str), _type(type)
{

}

ostream &operator <<(ostream &outs, const StrToken &t)
{
    outs << "|" << t._token << "|";

    return outs;
}

int StrToken :: type()
{
    return _type;
}

string StrToken :: type_string()
{
    switch (_type)
    {
        case 0:
        {
            return "UNKOWN";
        }
        case 1:
        {
            return "ALPHA"; // alphanumeric sequence
        }

        case 2:
        {
            return "NUMBER"; // real number
        }

        case 3:
        {
            return "PUNCTUATION";
        }

        case 4:
        {
            return "SPACE"; // whitespace
        }
    }
}

string StrToken :: token_str()
{
    return _token;
}
