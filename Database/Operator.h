#ifndef OPERATOR_H
#define OPERATOR_H

#include "ConditionalToken.h"

class Operator : public ConditionalToken
{
    public:

        virtual int type() const = 0;

        virtual ~Operator()
        {

        }

        virtual int get_precedence() const = 0;
};

#endif
