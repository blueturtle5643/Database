#ifndef QUEUE_H
#define QUEUE_H

#include "IteratedLists.h"

//Logic: Instead of an head pointer, pass an iteratedlist object into
//Queue for access to iteratedlist functions/nodefunctions. Also, since
//head isn't needed, keep track of the end of queue using an ITERATEDLIST
//pointer, not one created in queue. Iteratedlist pointer still needs
//functions defined

template <class ITEM_TYPE>
class Queue
{
    private:

        IteratedList<ITEM_TYPE> _queue; //Object from iteratedlist

        typename IteratedList<ITEM_TYPE>::Iterator _rear;   //iterator

        //from the iteratedlist

    public:

        class Iterator
        {
            private:

                typename IteratedList<ITEM_TYPE>::Iterator it;  //iterator
            //from iterator list

            public:

                friend class Queue; //give access to list to access _ptr

                Iterator()   //calls iteratedlist default constructor
                {

                }


                Iterator(typename IteratedList<ITEM_TYPE>::Iterator list_it)
                    : it(list_it)

                //constructor which takes an iterator from iteratedlist
                {
                    //reason to call it in header is based off inheritance
                    //but basically you call it off your "base class"
                }

                ITEM_TYPE& operator *()       //dereference operator
                {
                    return *it;
                }

                friend bool operator !=(const Iterator& left,
                                        const Iterator& right)
                //true if left != right
                {
                    return !(left == right);
                }

                friend bool operator ==(const Iterator& left,
                                        const Iterator& right)
                //true if left == right
                {
                    return left.it == right.it;
                }

                Iterator& operator++()
                //member operator: ++it; or ++it = new_value
                {
                    ++it;

                    return *this;
                }

                friend Iterator operator++(Iterator& it, int unused)
                {
                    Iterator copy(it);

                    it._ptr = it._ptr->_next;

                    return copy;
                }

        };

        Queue();            //CTOR


        //Big 3

        ~Queue();

        Queue(const Queue<ITEM_TYPE> &copyThis);

        Queue& operator =(const Queue& RHS);


        //Member Functions

        Iterator push(ITEM_TYPE item);  //inserts after at end of list

        ITEM_TYPE pop();        //deletes head

        ITEM_TYPE front() const;        //returns item in head

        bool empty() const;         //checks if empty

        void Print() const;

        Iterator Begin() const;      //Iterator to the head node

        Iterator End() const;       //Iterator to NULL
};

template <typename ITEM_TYPE>
Queue<ITEM_TYPE> :: Queue() : _queue(), _rear(nullptr)
{
    //initializationlist required to use iteratedlist constructors
}

template <typename ITEM_TYPE>
Queue<ITEM_TYPE> :: ~Queue()
{
    //shouldn't take the iteratedlist deconstructor so leaving empty is fine?
}


template <typename ITEM_TYPE>
Queue<ITEM_TYPE> :: Queue(const Queue <ITEM_TYPE> &copyThis)
: _queue(copyThis._queue), _rear(copyThis._rear)
{
   //uses initialization list as an inheritance proc on iteratedlist
    //constructor calls
}

template <typename ITEM_TYPE>
Queue<ITEM_TYPE>& Queue<ITEM_TYPE> :: operator =(const Queue& RHS)
{
    if(this == &RHS)
    {
        return *this;
    }

    _queue = RHS._queue;   //assigns iterators and object

    _rear = RHS._rear;

    return *this;
}

template <typename ITEM_TYPE>
typename Queue <ITEM_TYPE> :: Iterator Queue <ITEM_TYPE> ::
push(ITEM_TYPE item)
{
    _rear = _queue.InsertAfter(item, _rear);
                                                 //important that rear
    return _rear;                               //is reassigned after
}                                               //iterator movement

template <typename ITEM_TYPE>
ITEM_TYPE Queue <ITEM_TYPE> :: pop()
{
    ITEM_TYPE deleted =  _queue.Delete(_queue.Begin());

    if(empty())
    {
        _rear = nullptr;      //logic accounting for if list is empty
    }
    return deleted;
}

template <typename ITEM_TYPE>
ITEM_TYPE Queue <ITEM_TYPE> :: front() const
{
    if(empty())
    {
        return ITEM_TYPE();
    }
    else                        //logic for if list is empty
    {
        return _queue[0];
    }
}

template <typename ITEM_TYPE>
bool Queue <ITEM_TYPE> :: empty() const
{
    return _queue.empty();
}

template <typename ITEM_TYPE>
typename Queue <ITEM_TYPE> :: Iterator Queue <ITEM_TYPE> :: Begin() const
{
    return _queue.Begin();
}

template <typename ITEM_TYPE>
typename Queue <ITEM_TYPE> :: Iterator Queue <ITEM_TYPE> :: End() const
{
    return typename IteratedList<ITEM_TYPE>::Iterator(nullptr);
}

template <typename ITEM_TYPE>
void Queue <ITEM_TYPE> :: Print() const
{
    _queue.Print();
}

#endif // QUEUE_H
