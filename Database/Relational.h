#ifndef RELATIONAL_H
#define RELATIONAL_H

#include <string>

#include "Operator.h"
#include "Records.h"
#include "Field.h"
#include "Value.h"
#include "Map.h"
#include "MultiMap.h"

using namespace std;

class Relational : public Operator
{
    private:

        string _operator_str;

        int _precedence;

    public:

        typedef Map<string, MultiMap<string, long>> Indices_t;


        Relational(const string &operator_str, int precedence);

        virtual ~Relational();


        virtual int type() const;

        virtual int get_precedence() const;


        string str() const;

        Records apply(const Field &field, const Value &value,
                      Indices_t &indices) const;
};

#endif
