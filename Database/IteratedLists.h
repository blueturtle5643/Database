#ifndef ITERATEDLISTS_H
#define ITERATEDLISTS_H

#include "Node.h"

template <class ITEM_TYPE>
class IteratedList
{
    private:

        node<ITEM_TYPE>* _head_ptr;

    public:

        class Iterator
        {
            private:

                node<ITEM_TYPE>* _ptr;        //pointer being encapsulated

            public:

                friend class IteratedList; //give access to list to access _ptr

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

        IteratedList();            //CTOR


        //Big 3

        ~IteratedList();

        IteratedList(const IteratedList<ITEM_TYPE> &copyThis);

        IteratedList& operator =(const IteratedList& RHS);


        //Member Functions

        Iterator InsertHead(ITEM_TYPE i);   //insert at the head of list

        Iterator InsertAfter(ITEM_TYPE i, Iterator iMarker);
        //insert after marker

        Iterator InsertBefore(ITEM_TYPE i, Iterator iMarker);
        //insert before marker

        Iterator InsertSorted(ITEM_TYPE i);
        //insert in a sorted list


        ITEM_TYPE Delete(IteratedList<ITEM_TYPE>::Iterator iMarker);
        //delete node pointed to by marker

        void Print() const;

        Iterator Search(const ITEM_TYPE &key); //return Iterator to node [key]

        Iterator Prev(Iterator iMarker);    //previous node to marker


        ITEM_TYPE& operator[](int index);     //return item at position index

        Iterator Begin() const;      //Iterator to the head node

        Iterator End() const;       //Iterator to NULL

        Iterator LastNode() const;     //Iterator to the last node

        bool empty() const;

        template <typename U>         //Note the template arg U
        friend ostream& operator <<(ostream& outs, const IteratedList<U>& l);
};

template <typename ITEM_TYPE>
IteratedList<ITEM_TYPE> :: IteratedList()
{
    _head_ptr = nullptr;
}

template <typename ITEM_TYPE>
IteratedList<ITEM_TYPE> :: ~IteratedList()
{
    _clear_list(_head_ptr);
}


template <typename ITEM_TYPE>
IteratedList<ITEM_TYPE> :: IteratedList(const IteratedList <ITEM_TYPE>
                                        &copyThis)
{
   _head_ptr = _copy_list(copyThis._head_ptr);
}

template <typename ITEM_TYPE>
IteratedList<ITEM_TYPE>& IteratedList<ITEM_TYPE> :: operator =(const
                                                           IteratedList& RHS)
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
typename IteratedList <ITEM_TYPE> :: Iterator IteratedList <ITEM_TYPE> ::
InsertHead(const ITEM_TYPE item)
{
    return _insert_head(_head_ptr, item);
}

template <typename ITEM_TYPE>
typename IteratedList <ITEM_TYPE> :: Iterator IteratedList <ITEM_TYPE> ::
InsertBefore(const ITEM_TYPE item, Iterator iMarker)
{
    return _insert_before(_head_ptr,iMarker._ptr, item);
}

template <typename ITEM_TYPE>
typename IteratedList <ITEM_TYPE> :: Iterator IteratedList <ITEM_TYPE> ::
InsertAfter(const ITEM_TYPE item, Iterator iMarker)
{
    return _insert_after(_head_ptr,iMarker._ptr ,item);
}

template <typename ITEM_TYPE>
typename IteratedList <ITEM_TYPE> :: Iterator IteratedList <ITEM_TYPE> ::
InsertSorted(const ITEM_TYPE item)
{
    return _insert_sorted(_head_ptr, item);
}

template <typename ITEM_TYPE>
ITEM_TYPE IteratedList <ITEM_TYPE> :: Delete(IteratedList<ITEM_TYPE>::
                                           Iterator iMarker)
{
    return _delete_node(_head_ptr, iMarker._ptr);
}

template <typename ITEM_TYPE>
bool IteratedList <ITEM_TYPE> :: empty() const
{
   if(_head_ptr == nullptr)
   {
       return true;
   }
   else
   {
       return false;
   }
}

template <typename ITEM_TYPE>
typename IteratedList <ITEM_TYPE> :: Iterator IteratedList <ITEM_TYPE>
:: Begin()
const
{
    return _head_ptr;
}

template <typename ITEM_TYPE>
typename IteratedList <ITEM_TYPE> :: Iterator IteratedList <ITEM_TYPE> :: End()
const
{
    return nullptr;
}

template <typename ITEM_TYPE>
typename IteratedList <ITEM_TYPE> :: Iterator IteratedList <ITEM_TYPE> ::
Search(const ITEM_TYPE &key)
{
    return _search_list(_head_ptr, key);
}

template <typename ITEM_TYPE>
typename IteratedList <ITEM_TYPE> :: Iterator IteratedList <ITEM_TYPE> ::
Prev(Iterator iMarker)
{
    return _previous_node(_head_ptr, iMarker._ptr); //NOTE: iterator is an
}                                                   //object, need to take ptr

template <typename ITEM_TYPE>
void IteratedList <ITEM_TYPE> :: Print() const
{
    _print_list(_head_ptr);
}

template <typename ITEM_TYPE>
ITEM_TYPE& IteratedList<ITEM_TYPE>::operator[](int index)
{
    return _at(_head_ptr, index);
}

template <typename ITEM_TYPE>
typename IteratedList <ITEM_TYPE> :: Iterator IteratedList <ITEM_TYPE> ::
LastNode() const
{
    return _last_node(_head_ptr);
}

template<typename U>
typename IteratedList <U> :: ostream& operator <<(ostream& outs,
                                                const IteratedList<U>& l)
{
    return _print_list(l._head_ptr, outs);
}

#endif // ITERATEDLISTS_H
