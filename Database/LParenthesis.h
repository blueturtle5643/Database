#ifndef LPARENTHESIS_H
#define LPARENTHESIS_H

#include "ConditionalToken.h"

//using namespace std;

class LParenthesis : public ConditionalToken
{
    public:

        LParenthesis()
        {

        }

        virtual ~LParenthesis()
        {

        }

        virtual int type() const
        {
            return 6;
        }
};

#endif
