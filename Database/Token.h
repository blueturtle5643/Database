#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <ostream>

#include "TokenTypes.h"

using namespace std;

class Token
{
    private:

        string _token;

        TokenType _type;

        int _precedence;

    public:

        Token(string str, TokenType type, int precedence = -1); //Initialized Constructors

        friend ostream &operator<<(ostream &outs, const Token &t); // Extraction operator

        TokenType type() const; //Get for private variable type

        string token_str() const; //Get for private token

        int get_precedence() const;
};

#endif
