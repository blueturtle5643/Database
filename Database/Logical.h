#ifndef LOGICAL_H
#define LOGICAL_H

#include <string>

#include "Operator.h"
#include "Records.h"

using namespace std;

class Logical : public Operator
{
    private:

        string _operator_str;

        int _precedence;

        string uppercase(string str) const;

    public:

        Logical(const string &operator_str, int precedence);

        virtual ~Logical();


        virtual int type() const;

        virtual int get_precedence() const;


        string str() const;

        Records apply(const Records &left, const Records &right) const;


};

#endif
