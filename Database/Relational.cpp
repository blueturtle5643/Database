#include "Relational.h"

Relational :: Relational(const string &operator_str, int precedence)
    : _operator_str(operator_str), _precedence(precedence)
{

}

Relational :: ~Relational()
{

}

int Relational :: type() const
{
    return 3;
}

string Relational :: str() const
{
    return _operator_str;
}

int Relational :: get_precedence() const
{
    return _precedence;
}

Records Relational :: apply(const Field &field, const Value &value,
                            Indices_t &indices) const
{
    //bob

    //extract the indicies multimap with the field category

    MultiMap<string, long> &corresponding_values_mmap =
            indices[field.get_field_name()];

//    cout << corresponding_values_mmap << endl;

    const string value_str = value.get_value();

    vector<long> record_numbers_result;


    if (_operator_str == "=" && corresponding_values_mmap.contains(value_str))
    {
        record_numbers_result = corresponding_values_mmap[value_str];
    }

    else
    {
        //bob

        for (MultiMap<string,long> :: Iterator it =
             corresponding_values_mmap.begin();
                          it != corresponding_values_mmap.end(); it++)
        {
            if ((_operator_str == "<" && (*it).key < value_str) ||
                    (_operator_str == "<=" && (*it).key <= value_str) ||
                    (_operator_str == ">" && (*it).key > value_str) ||
                    (_operator_str == ">=" && (*it).key >= value_str))
            {
                vector <long> corresponding_rec_nums = (*it).values;

                //special vector insert, using specifics

                record_numbers_result.insert(record_numbers_result.end(),
                                             corresponding_rec_nums.begin(),
                                             corresponding_rec_nums.end());
            }
        }
    }

    return Records(record_numbers_result);
}
