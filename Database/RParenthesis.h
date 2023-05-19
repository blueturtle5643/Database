#ifndef RPARENTHESIS_H
#define RPARENTHESIS_H

#include "ConditionalToken.h"

class RParenthesis : public ConditionalToken
{
    public:

        RParenthesis()
        {

        }

        virtual ~RParenthesis()
        {

        }

        virtual int type() const
        {
            return 7;
        }
};

#endif
