#include "ShuntingYard.h"
#include "Operator.h"

void push_stack_operands_to_queue(Operator *token,
                                  int type,
                                  stack<Operator *> &stack,
                                  queue<ConditionalToken *> &output)
{
    //while stack is not empty, the last node of stack isn't left paren
    //if last node precedence is bigger than current token and isn't left
    //paren

    while (!stack.empty() &&
           (stack.top()->type() != 6 &&
            stack.top()->get_precedence() >= token->get_precedence()) &&
           type != 6)
    {
        output.push(dynamic_cast<ConditionalToken *>(stack.top()));

        stack.pop();
    }

    stack.push(token);
}

ShuntingYard :: ShuntingYard(const vector<ConditionalToken *> &infix)
{
    queue<ConditionalToken *> infix_q;

//    for (auto token : infix)
//    {
//        infix_q.push(token);
//    }

    for(int i = 0; i < infix.size(); i ++)
    {
        ConditionalToken* token = infix[i];

        infix_q.push(token);
    }

    _post_fix = _get_post_fix(infix_q);
}

queue<ConditionalToken *> ShuntingYard :: postfix() const
{
    return _post_fix;
}

queue<ConditionalToken *>
ShuntingYard :: _get_post_fix(queue<ConditionalToken *> infix)
{
    queue<ConditionalToken *> output;

    stack<Operator *> stack;

    while (!infix.empty())
    {
        ConditionalToken *token = infix.front();

        infix.pop();

        int type = token->type();

        switch (type)
        {
            case 4: //field
            {

            }

            case 5: //value
            {
                output.push(token);

                break;
            }

            case 2: //logical
            {

            }

            case 3: //relational
            {
                push_stack_operands_to_queue(dynamic_cast<Operator *>
                                             (token), type, stack, output);

                break;
            }

            case 6: //left paren
            {
                stack.push(dynamic_cast<Operator *>(token));

                break;
            }

            case 7: //right paren
            {
                while (stack.top()->type() != 6)
                {
                    output.push(dynamic_cast
                                <ConditionalToken *>(stack.top()));

                    stack.pop();
                }

                if (stack.top()->type() == 6)
                {
                    stack.pop();
                }

                break;
            }
        }
    }

    if (infix.empty())
    {
        while (!stack.empty())
        {
            output.push(dynamic_cast<ConditionalToken *>(stack.top()));

            stack.pop();
        }
    }

    return output;
}
