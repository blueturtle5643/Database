#ifndef FIELD_H
#define FIELD_H

#include <string>

#include "ConditionalToken.h"

using namespace std;

class Field : public ConditionalToken
{
    private:

        string _field_name;

    public:

        Field(const string &field_name);

        virtual ~Field();


        virtual int type() const;

        string get_field_name() const;
};

#endif
