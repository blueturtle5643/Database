#ifndef SHUNTINGYARD_H
#define SHUNTINGYARD_H

#include <vector>

#include "ConditionalToken.h"

#include "Queue.h"
#include "Stack.h"

#include <queue>
#include <stack>

using namespace std;

class ShuntingYard
{
    private:

        queue <ConditionalToken *>
        _get_post_fix(queue<ConditionalToken *> infix);

        queue <ConditionalToken *> _post_fix;

    public:

        ShuntingYard(const vector<ConditionalToken *> &infix);

        queue <ConditionalToken *> postfix() const;
};

#endif
