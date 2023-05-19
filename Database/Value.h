#ifndef VALUE_H
#define VALUE_H

#include <string>

#include "ConditionalToken.h"

using namespace std;

class Value : public ConditionalToken
{
    private:

        string _value;

    public:

        Value(const string &value);

        virtual ~Value();

        virtual int type() const;

        string get_value() const;
};

#endif
