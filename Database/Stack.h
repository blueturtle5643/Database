#ifndef STACK_H
#define STACK_H

#include "IteratedLists.h"

template <class ITEM_TYPE>
class Stack
{
    private:

        node<ITEM_TYPE>* _head_ptr;

    public:

        class Iterator
        {
            private:

                node<ITEM_TYPE>* _ptr;        //pointer being encapsulated

            public:

                friend class Stack; //give access to list to access _ptr

                Iterator()                                     //default ctor
                {
                    _ptr = NULL;
                }

                Iterator(node<ITEM_TYPE>* p)

                //Point Iterator to where p is pointing to
                {
                    _ptr = p;
                }


                ITEM_TYPE& operator *()       //dereference operator
                {
                    return _ptr -> _item;
                }


                ITEM_TYPE* operator ->()         //member access operator
                {
                    return _ptr;
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
                    return left._ptr == right._ptr;
                }

                Iterator& operator++()
                //member operator: ++it; or ++it = new_value
                {
                    if(_ptr != nullptr)
                    {
                        _ptr = _ptr->_next;
                    }

                    return *this;
                }

                friend Iterator operator++(Iterator& it, int unused)
                {
                    Iterator copy(it);

                    it._ptr = it._ptr->_next;

                    return copy;
                }

        };

        Stack();            //CTOR


        //Big 3

        ~Stack();

        Stack(const Stack<ITEM_TYPE> &copyThis);

        Stack& operator =(const Stack& RHS);


        //Member Functions

        Iterator push(ITEM_TYPE i);   //PUSH

        ITEM_TYPE pop();
        //delete node pointed to by marker

        bool empty() const;

        ITEM_TYPE top() const;

        Iterator Begin() const;      //Iterator to the head node

        Iterator End() const;

        void Print() const;


        template <typename U>         //Note the template arg U
        friend ostream& operator <<(ostream& outs, const Stack<U>& l);
};

template <typename ITEM_TYPE>
Stack<ITEM_TYPE> :: Stack()
{
    _head_ptr = nullptr;
}

template <typename ITEM_TYPE>
Stack<ITEM_TYPE> :: ~Stack()
{
    _clear_list(_head_ptr);
}


template <typename ITEM_TYPE>
Stack<ITEM_TYPE> :: Stack(const Stack <ITEM_TYPE> &copyThis)
{
   _head_ptr = _copy_list(copyThis._head_ptr);
}

template <typename ITEM_TYPE>
Stack<ITEM_TYPE>& Stack<ITEM_TYPE> :: operator =(const Stack& RHS)
{
    if(this == &RHS)
    {
        return *this;
    }

    _clear_list(_head_ptr);

    _head_ptr = _copy_list(RHS._head_ptr);

    return *this;
}

template <typename ITEM_TYPE>
typename Stack <ITEM_TYPE> :: Iterator Stack <ITEM_TYPE> ::        //AKA PUSH
push(const ITEM_TYPE item)
{
    return _insert_head(_head_ptr, item);
}

template <typename ITEM_TYPE>
ITEM_TYPE Stack <ITEM_TYPE> :: pop()
{
    return _delete_node(_head_ptr, _head_ptr);
}

template <typename ITEM_TYPE>
bool Stack <ITEM_TYPE> :: empty() const
{
    return _head_ptr == nullptr;
}

template <typename ITEM_TYPE>
ITEM_TYPE Stack <ITEM_TYPE> :: top() const
{
    return _head_ptr->_item;
}

template <typename ITEM_TYPE>
typename Stack <ITEM_TYPE> :: Iterator Stack <ITEM_TYPE> :: Begin() const
{
    return _head_ptr;
}

template <typename ITEM_TYPE>
typename Stack <ITEM_TYPE> :: Iterator Stack <ITEM_TYPE> :: End() const
{
    return nullptr;
}


#endif // STACK_H
