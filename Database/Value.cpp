#include "Value.h"

Value :: Value(const string &value) : _value(value)
{

}

Value :: ~Value()
{

}

int Value :: type() const
{
    return 5;
}

string Value :: get_value() const
{
    return _value;
}
