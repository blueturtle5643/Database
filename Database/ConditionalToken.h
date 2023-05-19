#ifndef CONDITIONALTOKEN_H
#define CONDITIONALTOKEN_H

class ConditionalToken
{
    public:

        virtual int type() const = 0;

        virtual ~ConditionalToken()
        {

        }
};

#endif
