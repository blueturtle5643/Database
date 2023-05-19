#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <ostream>

using namespace std;

class StrToken
{
    private:

        string _token;

        int _type;

    public:

        StrToken(); //Default Constructor

        StrToken(string str, int type); //Initialized Constructors

        friend ostream &operator<<(ostream &outs, const StrToken &t); // Extraction operator

        int type(); //Get for private variable type

        string type_string(); //Gives category as a string

        string token_str(); //Get for private token
};

#endif
