#include "RPN.h"
#include "Field.h"
#include "Value.h"
#include "Logical.h"
#include "Relational.h"

RPN :: ~RPN()
{
    for (int i = 0; i < in_between_calculations.size(); i++)
    {
        delete in_between_calculations[i];
    }
}

void RPN :: apply_binary_operator(ConditionalToken *token,
                                  stack<ConditionalToken *> &stack,
                                  Indices_t &indices)
{

    ConditionalToken *right = stack.top();

    stack.pop();

    ConditionalToken *left = stack.top();

    stack.pop();


    ConditionalToken *calculation_result = new Records;

    if (token->type() == 3) //relational
    {
        Relational *operator_ptr = dynamic_cast<Relational *>(token);

        Field *field_ptr = dynamic_cast<Field *>(left);

        Value *value_ptr = dynamic_cast<Value *>(right);

        //store calculation result in a records object

        Records temp = operator_ptr->apply(*field_ptr, *value_ptr, indices);

        //records result now has the vector of records

        dynamic_cast<Records *>(calculation_result)->
                set_records(temp.get_records());
    }

    else if (token->type() == 2)    //logical
    {
        Logical *operator_ptr = dynamic_cast<Logical *>(token);

        Records *r1_ptr = dynamic_cast<Records *>(left);

        Records *r2_ptr = dynamic_cast<Records *>(right);

        //union intersection depending on and or or

        Records temp = operator_ptr->apply(*r1_ptr, *r2_ptr);

        dynamic_cast<Records *>(calculation_result)->
                set_records(temp.get_records());
    }

    stack.push(calculation_result);

    //bob

    in_between_calculations.push_back(calculation_result);
}

Records RPN :: operator()(Indices_t &indices, queue<ConditionalToken *>
                          postfix)
{

    stack<ConditionalToken *> stack;

    while (!postfix.empty())
    {
        ConditionalToken *token = postfix.front();

        postfix.pop();

        int type = token->type();


        switch (type)
        {
            case 4: //field
            {

            }

            case 5: //value
            {
                stack.push(token);

                break;
            }

            case 2: //logical
            {

            }

            case 3: //relational
            {
                apply_binary_operator(token, stack, indices);

                break;
            }
        }
    }

    //bob

    vector<long> rec_nums = dynamic_cast<Records *>
            (stack.top())->get_records();

    return Records(rec_nums);
}
