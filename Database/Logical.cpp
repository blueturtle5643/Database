#include "Logical.h"

Logical :: Logical(const string &operator_str, int precedence)
    : _operator_str(operator_str), _precedence(precedence)
{
}

Logical :: ~Logical()
{

}

int Logical :: type() const
{
    return 2;
}

string Logical :: str() const
{
    return _operator_str;
}

int Logical :: get_precedence() const
{
    return _precedence;
}

Records Logical :: apply(const Records &left, const Records &right) const
{
    if (uppercase(_operator_str) == "AND")
    {
        return left.Intersection(right);
    }

    else if (uppercase(_operator_str) == "OR")
    {
        return left.Union(right);
    }

    return Records();
}

string Logical :: uppercase(string str) const
{
    for (int i = 0; i < str.size(); i++)
    {
        str[i] = toupper(str[i]);
    }

    return str;
}
