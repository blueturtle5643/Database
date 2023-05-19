#ifndef RECORDS_H
#define RECORDS_H


#include <vector>

#include "ConditionalToken.h"

using namespace std;

class Records : public ConditionalToken
{
    private:

        vector<long> _records;

    public:

        Records();

        Records(const vector<long> &initial_records);


        virtual ~Records();

        virtual int type() const;


        void set_records(vector<long> records);

        vector<long> get_records() const;

        bool empty() const;


        Records Union(const Records &other) const;

        Records Intersection(const Records &other) const;
};

#endif
