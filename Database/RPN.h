#ifndef RPN_H
#define RPN_H

#include "Queue.h"
#include "Stack.h"

#include "Records.h"
#include "ConditionalToken.h"
#include "Map.h"
#include "MultiMap.h"
#include "Operator.h"

#include <stack>
#include <queue>

using namespace std;

typedef Map<string, MultiMap<string, long>> Indices_t;

class RPN
{
    private:

      void apply_binary_operator(ConditionalToken *token,
                                 stack<ConditionalToken *> &stack,
                                 Indices_t &indices);

      void push_stack_operands_to_queue(Operator *token,
                                        int type,
                                        stack<Operator *> &stack,
                                        queue<ConditionalToken *> &output);

      vector<ConditionalToken *> in_between_calculations;

    public:

      ~RPN();

      Records operator()(Indices_t &indices,
                         queue<ConditionalToken *> postfix);
};

#endif
