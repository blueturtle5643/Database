#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

template <typename T>
struct node
{
    //Variables

    T _item;                                // "items in an crate"

    node<T>* _next;                     // "pointer pointing at next "crate"

    //constructor with item set to default type and next pointer to null

    node(const T& item=T(), node<T> *next = nullptr)//:_item(item), _next(next)
    {
        _item = item;

        _next = next;
    }

    //insertion operator

    friend ostream& operator<<(ostream& outs, const node<T>& node)
    {
        outs << "[" << node._item << "] -> ";

        return outs;
    }
};

template<typename T>
ostream& _print_list(node<T>* head_ptr, ostream& outs = cout);



template<typename T>
node<T>* _insert_head(node<T>* &head_ptr, const T& item)
{
    //LOGIC: Inserts before

    //1: Create a new node with item

    node<T>* temp = new node<T>(item);

    //2. New nodes (next) sticker becomes passed in pointers sticker

    temp->_next = head_ptr;

    //3. passed in pointer is now pointing to the new node

    head_ptr = temp;

    return head_ptr;
}

template<typename T>
node<T>* _insert_after(node<T>* &head_ptr, node<T>* afterThis, const T &item)
{
    //LOGIC: Inserts node after the passed in node

    if(afterThis == nullptr && head_ptr != nullptr)

     //accounts for if there are no nodes
    {
        //cout << "\nInsert After: afterThis is null." << endl;

        return nullptr;
    }

    if(head_ptr == nullptr)     //accounts for if head is null, creates a node
    {
        return _insert_head(head_ptr, item);
    }

    node<T>* newly_inserted_node = _insert_head(afterThis->_next, item);

    //passing in (afterThis ->next) gives you the node after afterthis,
    //but since insert head is inserting before, it puts it in between,
    //which is basically inserting after (afterThis) node

    afterThis->_next = newly_inserted_node;

    //assigning (afterThis -> next) to new node

    //afterThis ->_next = _insert_head(afterThis->_next, item);

    //how to do it in one line?

    return afterThis->_next;
}

template <typename T>
node<T>* _insert_before(node<T>* &head_ptr, node<T>* beforeThis, const T &item)
{
    //LOGIC: built off of inserthead with failsafes

    if(beforeThis == nullptr && head_ptr != nullptr)    //accounts for if there
                                                            //are no nodes
    {
        //cout << "\nInsert Before: afterThis is null." << endl;

        return nullptr;
    }

    if(head_ptr == nullptr)     //creates new node if head is null
    {
        return _insert_head(head_ptr, item);
    }

    node<T>* prev = _previous_node(head_ptr, beforeThis);

    //uses previousnode function to fulfill repetitive failsafes

    node<T>* newly_inserted = _insert_head(beforeThis, item);

    //insert head logic same as insert before

    if(prev != nullptr)     //if previous node failed any checks
    {
        prev->_next = newly_inserted; //previous next would point to new node
    }

//    cout << "\nBefore this is: " << *beforeThis << endl;

//    cout << "\nHead pointer is: " << *head_ptr << endl;

    //   {0}  [1]   2   3
//             b
    if(beforeThis ->_next == head_ptr)
    {
        head_ptr = newly_inserted;//BUG BUG BUG BUG BUG BUG BUG TEST TEST TEST
    }

    return newly_inserted;

}

template <typename T>
node<T>* _previous_node(node<T>* head, node<T>* prevToThis)
{
    //LOGIC: bunch of failsafes to check if you can move to previous node
    //safely, can be used in other functions with all checks


    //can't move back if head is null(AKA no nodes), can't move back if
    //the only node is head(AKA 1 node)

    if(head == nullptr || prevToThis == head)
    {
        //cout << "\nPrevious Node: Head is null or previous is null." << endl;

        return nullptr;
    }

    node<T>* walker = head;  //creates a walker pointing to beginning of list


    //walker needed to get previous node since you can't move backwards in
    //singly linked lists

    //while walker doesn't equal to previous and walker hasn't hit the end

    //IMPORTANT: uses (walker -> next) so that it will stop at the node
    //previous to the node you want

    while(walker->_next != prevToThis && walker->_next != nullptr)
    {
        walker = _next_node(head, walker);  //uses nextnode function

        //for additional checks
    }

    return walker;
}

template <typename T>
node<T>* _next_node(node<T>* head, node<T>* nextToThis)
{
    //LOGIC: bunch of failsafes to check if you can move to next node
    //safely, can be used in other functions with all checks


    //if head is null (AKA no nodes) or if next is null (AKA bad input)

    if(head == nullptr || nextToThis == nullptr)
    {
        //cout << "\nNext Node: Head is null or next is null." << endl;

        return nullptr;
    }

    return nextToThis->_next;
}

template <typename T>
T _delete_node(node<T>* &head, node<T>* deleteThis)
{
    //LOGIC: 3 different cases for deleting a node, one where node is
    //the first node AKA headpointer node, one where its in between 2 nodes
    //and one


    //ONE NODE CASE:

    //if head isn't null(AKA no nodes) and if its the only node AKA next is
    //null

    if(head != nullptr && head->_next == nullptr)
    {
        T copy(head->_item);    //copy constructor that takes items

        delete head;            //deletes node

        head = nullptr;         //makes sure head is set to null

        return copy;            //returns contents of node
    }

    //failsafe for if head is null or delete this is null AKA bad input

    if(head == nullptr || deleteThis == nullptr)
    {
        //cout << "\nDelete Node: Head is null or deletethis is null." << endl;

        return T(); //return 0 of data type
    }

    //create 2 pointers for nodes before and after node to delete, performing
    //failsafe checks

    node<T>* prev = _previous_node(head, deleteThis);

    node<T>* next = _next_node(head, deleteThis);


    //if checks for previous go through

    if(prev != nullptr)
    {
        prev->_next = next;     //previous node will now point to next
                                //removing the node in between
    }

    T copy(deleteThis->_item);  //copy constructor takes contents of node

    delete deleteThis;          //deletes node

    if(deleteThis == head)      //if node was first node in list being deleted
                                //the head pointr needs to be reassigned
    {
        head = next;            //head becomes next
    }

    return copy;                //return contents
}

template <typename T>
node<T>* _copy_list(node<T>* head)
{
    //LOGIC: copies contents of old list into new AKA scanning each node
    //taking contents and moving into new nodes which are being linked

    //IMPORTANT: head isn't passed by reference allowing us to use head
    //to move through list to extract contents from each node instead of using
    //a walker

    if(head == nullptr) //if there's nothing to copy
    {
        //cout << "\nCopy List: Head is null." << endl;

        return nullptr;
    }

    else
    {
        //creates a node with the contents of headpointers items

        node<T>* copy_head = new node<T>(head->_item);

        //creates a walker pointing at new node

        node<T>* walker = copy_head;

        //advances head to next node

        head = head->_next;

        //loop until end of list

        while(head != nullptr)
        {
            //creates an list using insertafterm taking items from nodes
            //in head which advances, inserting into walker which is afterThis
            //with copy_head being the new head pointer of new list

            _insert_after(copy_head, walker, head->_item);

            head = head->_next; //advance head to get old node items

            walker = walker->_next; //advance walker to continue creating list
        }

        return copy_head;   //return new list pointer
    }
}

template <typename T>
void _clear_list(node<T>* &head)
{
    //LOGIC: runs through list to delete every node

    //IMPORTANT: headpointer is passed by reference, and although you can
    //create an walker to move through list, an lesson is that when deleting
    //list, it doesn't matter if you move head since everything is being
    //deleted anyways

    while(head != nullptr)
    {
        _delete_node(head, head);
    }

    head = nullptr; //when list is deleted, headpointer should be set back
                    //to null
}

template <typename T>
T& _at(node<T>* head, int pos)
{
    //LOGIC: extract item in the position of the list aka certain node

    //IMPORTANT: head isn't being passed by reference so use it

    for(int i = 0; i < pos; i++)    //since position # can correspond to
    {                               //the nth node in an list, for loop to it
        head = head->_next;
    }                               //advance head

    return head->_item;             //should stop at the position of desired
                                    //node and return item
}

template <typename T>
node<T>* _search_list(node<T>* head, T key)
{
    //LOGIC: extract location of first occurance of item

    //IMPORTANT: head isn't being passed by reference so use it

    if(head == nullptr)
    {
        return nullptr;
    }

    //while head hasn't reached end and the key hasn't been found

    while(head ->_next != nullptr && head->_item != key)

                                        //ADDED ->next to stop properly
    {
        head = head->_next;
    }

    //when found, return pointer

    if(head->_item == key)
    {
        return head;
    }

    //if nothing is found return nullptr
    return nullptr;
}

template <typename T>
node<T>* _where_this_goes(node<T>* head, T item, bool ascending = true)
{
    //LOGIC: assuming an sorted list of ascending or descending,
    //goes through list with 2 walkers to with the trailing walker to be
    //returned as the insertafter variable

    //IMPORTANT: head isn't being passed by reference so use it

    if(head == nullptr)     //failsafe for empty list
    {
        //cout << "\nWhere this goes: Head is null." << endl;

        return nullptr;
    }

    //create a walker for head and another walker thats one ahead of it

    node<T>* walker = head;

    node<T>* next = walker->_next;

    //considering if an sorted list is ascending

    if(ascending == true)
    {
        //scans items to see if passed in item is bigger than list items
        //stops nextpointer which is ahead of walker if it reaches end
        //ensuring the normal walker to be spot to insertafter

        while(next != nullptr && item > next->_item)
        {
            walker = walker->_next; //advance both walkers

            next = walker->_next;
        }
    }
            //logic for descending sorted list

    //If you're inserting 16: 32 16 13 12 11

    if(ascending == false)
    {
        while(next != nullptr && item < next->_item)
        {
            walker = walker->_next;

            next = walker->_next;
        }
    }

    return walker;      //returns walker AKA afterThis node
}

template <typename T>
node<T>* _insert_sorted(node<T>* &head, T item, bool ascending = true)
{
    //LOGIC: runs wherethisgoes and determines if a new node with item
    //should go into list

    //uses wherethisgoes and assigns a position to it

    node<T>* position = _where_this_goes(head, item, ascending);

    //if position didn't fail any checks from wherethisgoes BUT
    //there are duplicate values (AKA item you're trying to insert is also in
    //list) then null is returned

    //if(position->_next != nullptr && position->_next->_item == item)

    //BUG BUG BUG BUG BUG TEST TEST TEST

    if(position == nullptr)
    {
        return _insert_head(head, item);
    }

    //If you're inserting 16: 12 14 16

    if(position->_next != nullptr && position->_next->_item == item &&
            ascending == true)
    {
        //cout << "\nInsert Sorted: Wherethis goees test failed"
                //" or wherethisgoes value is equal to item." << endl;

        return _insert_after(head, position, item);
    }

    //If you're inserting 32: 32 16 13 12 11

    if(position->_next != nullptr && position->_item == item && ascending
            == false)
    {
        //cout << "\nInsert Sorted: Wherethis goees test failed"
                //" or wherethisgoes value is equal to item." << endl;

        return _insert_before(head, position, item);
    }

    // If you're inserting 2: 10 20 30

    if(position ->_item > item && ascending == true)

                                        //BUG BUG BUG BUG BUG TEST TEST TEST
    {
        return _insert_before(head, position, item);
    }

    // If you're inserting 18: 16 14 12

    if(position->_item < item && ascending == false)
    {
        return _insert_before(head, position, item);
    }
    //inserts new node with value after the wherethisgoes node

    else
    {
        return _insert_after(head, position, item);
    }
}

template <typename T>
node<T>* _insert_sorted_and_add(node<T>* &head, T item, bool ascending = true)
{
    //LOGIC: runs wherethisgoes and determines if a new node with item
    //should go into list

    //uses wherethisgoes and assigns a position to it

    node<T>* position = _where_this_goes(head, item, ascending);

    //cout << "\nPosition is: " << *position << endl;

    //if position didn't fail any checks from wherethisgoes BUT
    //there are duplicate values (AKA item you're trying to insert is also in
    //list) then null is returned

    //if(position->_next != nullptr && position->_next->_item == item)

    //BUG BUG BUG BUG BUG TEST TEST TEST

    if(position == nullptr)
    {
        return _insert_head(head, item);
    }

    //If you're inserting 16: 12 14 16

    if(position->_next != nullptr && position->_next->_item == item &&
            ascending == true)
    {
        //cout << "\nInsert Sorted: Wherethis goees test failed"
                //" or wherethisgoes value is equal to item." << endl;

        position->_next->_item += item;

        return position->_next;
    }

    // If you're inserting 10: 10 20 30

    if(position ->_item == item && ascending == true)

                                        //BUG BUG BUG BUG BUG TEST TEST TEST
    {
        position ->_item += item;

        return position;
    }

    //If you're inserting 32: 32 16 13 12 11

    if(position->_next != nullptr && position->_next->_item == item && ascending
            == false)
    {
        //cout << "\nInsert Sorted: Wherethis goees test failed"
                //" or wherethisgoes value is equal to item." << endl;

        position->_next->_item += item;

        return position;
    }

    if(position->_item == item && ascending == false)

                                        //BUG BUG BUG BUG BUG TEST TEST TEST
    {
        position ->_item += item;

        return position;
    }

    //If you're inserting 16: 32 16 13 12 11

    else
    {
        return _insert_sorted(head, item, ascending);
    }
}

template <typename T>
node<T>* _last_node(node<T>* head)
{
    //LOGIC: runs wherethisgoes and determines if a new node with item
    //should go into list

    //IMPORTANT: head isn't being passed by reference so use it

    //runs head down the list

    while(head != nullptr && head->_next != nullptr)
    {
        head = head->_next;
    }

    return head;
}

template<typename T>
ostream& _print_list(node<T>* head_ptr, ostream& outs)
{
    cout << endl;

    outs << "H -> ";

    for(node<T> *w = head_ptr; w != nullptr; w = w -> _next)
    {
        outs << *w;
    }

    outs << " |||";

    cout << endl;

    return outs;
}

#endif // NODE_H
