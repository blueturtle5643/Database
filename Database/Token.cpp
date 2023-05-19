#include "Token.h"

Token :: Token(string str, TokenType type, int precedence)
    : _token(str), _type(type), _precedence(precedence)
{

}

ostream &operator <<(ostream &outs, const Token &t)
{
    outs << "|" << t._token << "|";

    return outs;
}

TokenType Token :: type() const
{
    return _type;
}

string Token :: token_str() const
{
    return _token;
}

int Token :: get_precedence() const
{
    return _precedence;
}
