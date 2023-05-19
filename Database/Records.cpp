#include "Records.h"

#include "B+Tree.h"

Records :: Records()
{

}

Records :: Records(const vector<long> &initial_records)
    : _records(initial_records)
{

}

Records :: ~Records()
{

}

int Records :: type() const
{
    return 1;
}

bool Records :: empty() const
{
    return _records.empty();
}

vector<long> Records :: get_records() const
{
    return _records;
}

void Records :: set_records(vector<long> records)
{
    _records = records;
}

Records Records :: Union(const Records &other) const
{
    BPlusTree<long> all_records;


    // insert all record numbers first

    for (int i = 0; i < _records.size(); i++)
    {
        all_records.insert(_records[i]);
    }


    // insert missing record numbers from other

    for (int i = 0; i < other._records.size(); i++)
    {
        if (!all_records.contains(other._records[i]))
        {
            all_records.insert(other._records[i]);
        }
    }


    // put them all into a vector

    vector<long> results_vec;

    //bob

    for (BPlusTree <long> :: Iterator it = all_records.begin();
         it != all_records.end(); it++)
    {
        results_vec.push_back(*it);
    }

    return Records(results_vec);
}

Records Records :: Intersection(const Records &other) const
{

    BPlusTree<long> LHS_records;

    // insert LHS record numbers into tree

    for (int i = 0; i < _records.size(); i++)
    {
        LHS_records.insert(_records[i]);
    }

    // iterate through other's record numbers, store if common to both

    vector<long> common;

    for (int i = 0; i < other._records.size(); i++)
    {
        if (LHS_records.contains(other._records[i]))
        {
            common.push_back(other._records[i]);
        }
    }

    return Records(common);
}
