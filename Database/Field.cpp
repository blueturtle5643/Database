#include "Field.h"

Field :: Field(const string &field_name) : _field_name(field_name)
{

}

Field :: ~Field()
{

}

int Field :: type() const
{
    return 4;
}

string Field :: get_field_name() const
{
    return _field_name;
}
