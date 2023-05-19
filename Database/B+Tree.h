#ifndef BTREE_H
#define BTREE_H

#include <iomanip>
#include <cassert>

#include "Array_Utility.h"


template <typename T>
class BPlusTree
{
    private:

        static const int MINIMUM = 1;

        static const int MAXIMUM = 2 * MINIMUM;


        bool dups_ok; // true if duplicate keys may be inserted

        int data_count; // number of data elements

        T data[MAXIMUM + 1]; // holds the keys

        int child_count; // number of children


        BPlusTree<T>* subset[MAXIMUM + 2]; // suBPlusTrees

        BPlusTree<T>* next;



        bool is_leaf() const { return child_count == 0; }

        T *find_ptr(const T &entry); // return a pointer to this key. nullptr if not there

        const T *find_ptr(const T &entry) const;


        // insert element functions

        void loose_insert(const T &entry); // allows MAXIMUM + 1 data elements in the root

        void fix_excess(int i); // fix excess of data elements in child i



        const BPlusTree<T> *get_smallest_node() const;

        void get_smallest(T &entry); // entry := leftmost leaf

        void get_biggest(T &entry); // entry := rightmost leaf



        void remove_biggest(T &entry); //remove the biggest child of this tree->entry

        void transfer_left(int i); //transfer one element LEFT from child i

        void transfer_right(int i); //transfer one element RIGHT from child i

        BPlusTree<T>* merge_with_next_subset(int i); //merge subset i with subset i+1

        void loose_remove(const T &entry); //allows MINIMUM-1 data elements in the root

        BPlusTree<T>* fix_shortage(int i); //fix shortage of data elements in child i
                                           // and return the smallest key in this suBPlusTree
    public:

        class Iterator
        {
            private:

                const BPlusTree<T>* it;

                int key_ptr;

            public:

                friend class BPlusTree;

                Iterator(const BPlusTree<T>* _it = nullptr, int _key_ptr = 0)
                    : it(_it), key_ptr(_key_ptr)
                {

                }

                T operator*()
                {
                    assert(key_ptr < it->data_count);   //is it valid???

                    return it->data[key_ptr];
                }

                // post-increment

                Iterator operator++(int un_used)
                {
                    if (it != nullptr)
                    {
                        Iterator copy = *this;

                        if (key_ptr < it->data_count - 1)
                        {
                            ++key_ptr;
                        }

                        else
                        {
                            it = it->next;

                            key_ptr = 0;
                        }

                        return copy;
                    }

                    return *this;
                }

                // pre-increment

                Iterator operator++()
                {
                    if (it != nullptr)
                    {
                        if (key_ptr < it->data_count - 1)
                        {
                            ++key_ptr;
                        }

                        else
                        {
                            it = it->next;

                            key_ptr = 0;
                        }
                    }

                    return *this;
                }


                const T *operator->()
                {
                    return &(it->data[key_ptr]);
                }

                friend bool operator==(const Iterator &lhs,
                                       const Iterator &rhs)
                {
                    return lhs.it == rhs.it && lhs.key_ptr == rhs.key_ptr;
                }

                friend bool operator!=(const Iterator &lhs,
                                       const Iterator &rhs)
                {
                    return lhs.it != rhs.it;
                }

                void print_Iterator()
                {
                    cout << *it;
                }

                bool is_nullptr()
                {
                    return !it;
                }
        };

        BPlusTree(bool dups = false);

        //big 3

        BPlusTree(const BPlusTree &other);

        ~BPlusTree();

        BPlusTree &operator=(const BPlusTree &RHS);



        void insert(const T &entry);

        void remove(const T &entry); //remove entry from the tree

        void clear_tree(); // clear this object (delete all nodes etc.)



        // copy other into this object

        void copy_tree(const BPlusTree<T> &other, BPlusTree<T> *&last_leaf);



        //void copy_tree(const BPlusTree<T> &other, stack<BPlusTree<T> *> &s);

        bool contains(const T &entry) const; // true if entry can be found in the array

        T &get(const T &entry); // return a reference to entry in the tree

        const T &get(const T &entry) const; // return a reference to entry in the tree

        T &get_existing(const T &entry); // return a reference to entry in the tree

        Iterator find(const T &entry); // return an iterator to this key. nullptr if not there

        Iterator find(const T &entry) const;



        Iterator lower_bound(const T &key); //return first that goes NOT BEFORE
                                            // key entry or next if does not
                                            // exist >= entry
        Iterator upper_bound(const T &key); //return first that goes AFTER key



        int size() const; //count the number of elements in the tree

        bool empty() const;

        void print_tree(int level = 0,
                        ostream &outs = cout) const; //print a readable version of the tree

        friend ostream &operator<<(ostream &outs,
                                   const BPlusTree<T> &print_me)
        {
            print_me.print_tree(0, outs);

            return outs;
        }



        Iterator begin() const;

        Iterator end() const;

        bool is_valid();
};


template <typename T>
BPlusTree <T> :: BPlusTree(bool dups)
    : dups_ok(dups), data_count(0), child_count(0), next(nullptr)
{
    for (int i = 0; i < MAXIMUM + 2; i++)
    {
        subset[i] = nullptr;
    }
}

template <typename T>
BPlusTree <T> :: BPlusTree(const BPlusTree &other)
    : dups_ok(other.dups_ok), data_count(other.data_count),
      child_count(other.child_count), next(other.next)
{
    BPlusTree<T> *garbage = nullptr;

    copy_tree(other, garbage);
}

template <typename T>
BPlusTree <T> :: ~BPlusTree()
{
    clear_tree();
}

template <typename T>
BPlusTree <T> &BPlusTree <T> :: operator =(const BPlusTree &RHS)
{
    if (this != &RHS)
    {
        clear_tree();

        BPlusTree<T> *useless = nullptr;

        copy_tree(RHS, useless);


        dups_ok = RHS.dups_ok; //forgot about these


        data_count = RHS.data_count;

        child_count = RHS.child_count;
    }

    return *this;
}

template <typename T>
void BPlusTree<T> :: loose_insert(const T &entry)
{
    //    if (dups_ok)
    //    {
    //        T *dup_insertion = find(entry);

    //        if (dup_insertion != nullptr)
    //        {
    //            *dup_insertion = entry;

    //            return;
    //        }
    //    }

    int insertion_point = first_ge(data, data_count, entry);

    if (is_leaf())
    {
        insert_item(data, insertion_point, data_count, entry);
    }

    //changed logic: recursion, but after fix excess if the insertion was a
    //leaf then you reassign the next pointers

    else
    {
        subset[insertion_point]->loose_insert(entry);

        if (subset[insertion_point]->data_count == MAXIMUM + 1)
        {
            BPlusTree<T> *next_node = subset[insertion_point]->next;

            fix_excess(insertion_point);


            //pointer assignment

            if (subset[insertion_point]->is_leaf())
            {
                subset[insertion_point]->next = subset[insertion_point + 1];


                //left to new

                if (subset[insertion_point + 1] != nullptr)
                {
                    subset[insertion_point + 1]->next = next_node;

                    //new to right
                }
            }
        }
    }
}

template <typename T>
void BPlusTree<T> :: fix_excess(int i)
{
    int half_data_size = 0;

    if ((MAXIMUM + 1) % 2 == 1)
    {
        half_data_size = (MAXIMUM + 1) / 2;
    }
    else
    {
        half_data_size = (MAXIMUM + 1) / 2 - 1;
    }

    // move middle item to the parent

    T middle_item = subset[i]->data[half_data_size]; //establishes middle

    //might need to delete item instead of leaving it there because it'll
    //get printed?

    int excess_insertion_point = first_ge(data, data_count, middle_item);

    //finds proper insertion point for the parent

    insert_item(data, excess_insertion_point, data_count, middle_item);

    //inserts at proper location

    BPlusTree<T> *new_child = new BPlusTree<T>();

    // add new subset pointer, which points to new child

    insert_item(subset, excess_insertion_point + 1, child_count,
                new_child);

    //following the logic of fix excess:

    //1. delete item in child array

    //2. split the child array

    //3. split the subset array

    delete_item(subset[i]->data, half_data_size, subset[i]->data_count,
                middle_item);

    split(subset[i]->data, subset[i]->data_count, new_child->data,
          new_child->data_count);

    split(subset[i]->subset, subset[i]->child_count, new_child->subset,
          new_child->child_count);

    //if its the bottom, insert a duplicate

    if (subset[i]->is_leaf())
    {
        //cout << "\nI'm inserting a duplicate!" << endl;

        //print_array(subset[i + 1]->data, subset[i + 1]->data_count);

        //cout << subset[i + 1]->data_count;

        insert_item(subset[i + 1]->data, 0, subset[i + 1]->data_count, middle_item);

        //cout << subset[i + 1]->data_count;

        //print_array(subset[i + 1]->data, subset[i + 1]->data_count);
    }
}

template <typename T>
void BPlusTree<T> :: insert(const T &entry)
{
    if (empty())
    {
        data[0] = entry;

        data_count++;
    }

    //Everything shifted into contains to prevent duplicates for now

    else if (!contains(entry))
    {
        loose_insert(entry);

        if (data_count == MAXIMUM + 1)
        {
            BPlusTree<T> *excess = new BPlusTree<T>();

            copy_array(excess->data, data, excess->data_count, data_count);

            copy_array(excess->subset, subset, excess->child_count,
                       child_count);

            data_count = 0;

            child_count = 1;

            subset[0] = excess;

            fix_excess(0);

            subset[0]->next = subset[1];
        }
    }
}

template <typename T>
typename BPlusTree <T> :: Iterator BPlusTree <T> :: find(const T &entry)
{
    if (!empty())
    {
        int i = first_ge(data, data_count, entry);

        if (is_leaf())
        {
            if (i < data_count && data[i] == entry)
            {
                return Iterator(this, i);
            }
        }

        else
        {
            if (i == data_count || entry < data[i])
            {
                return subset[i]->find(entry);
            }

            else
            {
                return subset[i + 1]->find(entry);
            }
        }
    }

    return Iterator(nullptr, 0);
}
template <typename T>
typename BPlusTree <T> :: Iterator BPlusTree <T> :: find(const T &entry) const
{
    if (!empty())
    {

        int i = first_ge(data, data_count, entry);

        if (is_leaf())
        {
            if (i < data_count && data[i] == entry)
            {
                return Iterator(this, i);
            }
        }

        else
        {
            if (i == data_count || entry < data[i])
            {
                return subset[i]->find(entry);
            }

            else
            {
                return subset[i + 1]->find(entry);
            }
        }
    }

    return Iterator(nullptr, 0);
}

template <typename T>
T &BPlusTree<T> :: get(const T &entry)
{
    //Assuming get returns get existing and handles the check for find/contains

    if (!contains(entry))
    {
        insert(entry);
    }

    return get_existing(entry);
}

template <typename T>
T &BPlusTree<T> :: get_existing(const T &entry)
{
    return *find_ptr(entry);
}

template <typename T>
const T &BPlusTree<T> :: get(const T &entry) const
{
    return *find_ptr(entry);
}

template <typename T>
bool BPlusTree <T> :: contains(const T &entry) const
{
    return find(entry) != end();
}

template <typename T>
void BPlusTree <T> :: clear_tree()
{
    if (!is_leaf())
    {
        for (int i = 0; i < child_count; i++)
        {
            subset[i]->clear_tree();


            delete subset[i];

            subset[i] = nullptr;
        }

        child_count = 0;

        data_count = 0;
    }
}

template <typename T>
void BPlusTree <T> :: copy_tree(const BPlusTree<T> &other,
                                BPlusTree<T>* &last_leaf)
{
    copy_array(data, other.data, data_count, other.data_count);

    if (!other.is_leaf())
    {
        for (int i = 0; i < other.child_count; i++)
        {
            subset[i] = new BPlusTree<T>;

            subset[i]->copy_tree(*(other.subset[i]), last_leaf);
        }

        child_count = other.child_count;

        data_count = other.data_count;
    }

    //leaf tree nodes, if not the last leaf then connect pointer of next node
    //to current node

    else
    {
        if (last_leaf != nullptr)
        {
            last_leaf->next = this;
        }

        last_leaf = this;
    }
}

template <typename T>
void BPlusTree <T> :: print_tree(int level, ostream &outs) const
{
    if (!is_leaf())
    {
        for (int i = child_count - 1; i >= 0; i--)
        {
            subset[i]->print_tree(level + 1, outs);

            if (i != 0)
            {
                outs << setw(4 * level) << '[' << data[i - 1] << ']' << endl;
            }
        }
    }

    if (is_leaf())
    {
        for (int i = data_count - 1; i >= 0; i--)
        {
            outs << setw(4 * level) << '[' << data[i] << ']' << endl;
        }
    }
}

template <typename T>
const BPlusTree <T>* BPlusTree <T> :: get_smallest_node() const
{
    if (!is_leaf())
    {
        return subset[0]->get_smallest_node();
    }

    return this;
}

template <typename T>
void BPlusTree <T> :: get_smallest(T &entry)
{

//    cout << "\nEntry is: " << entry << endl;

//    cout << "\nData is: " << data[0] << endl;

    entry = get_smallest_node()->data[0];   //returning reference to value

//    cout << "\nEntry after is: " << entry << endl;

//    cout << "\nData after is: " << data[0] << endl;
}

template <typename T>
void BPlusTree <T> :: get_biggest(T &entry)
{
    if (!is_leaf()) //iterate to rightmost bottom
    {
        subset[child_count - 1]->get_biggest(entry);
    }

    else
    {
        entry = data[data_count - 1];
    }
}

template <typename T>
typename BPlusTree <T> :: Iterator BPlusTree <T> :: begin() const
{
    if (empty())
    {
        return end();
    }

    return Iterator(get_smallest_node());
}

template <typename T>
typename BPlusTree <T> :: Iterator BPlusTree <T> :: end() const
{
    return nullptr;
}

template <typename T>
typename BPlusTree <T> :: Iterator BPlusTree <T> :: lower_bound(const T &key)
{
    int i = first_ge(data, data_count, key);

    if (is_leaf())
    {
        if (i < data_count)
        {
            return Iterator(this, i);
        }

        else
        {
            return Iterator(next, 0);
        }
    }

    else
    {
        if (i == data_count)
        {
            return subset[i]->lower_bound(key);
        }

        else if (key < data[i])
        {
            return subset[i]->lower_bound(key);
        }

        else
        {
            return subset[i + 1]->lower_bound(key);
        }
    }

    return Iterator(nullptr, 0); // should never be reached
}

template <typename T>
typename BPlusTree <T> :: Iterator BPlusTree <T> :: upper_bound(const T &key)
{
    typename BPlusTree<T> :: Iterator it = lower_bound(key);

    if (*it == key)
    {
        it++;
    }

    return it;
}

template <typename T>
int BPlusTree <T> :: size() const
{
    int count = 0;

    if (!empty())
    {
        // go to left-most

        const BPlusTree<T> *current = this;

        while (current->child_count > 0)
        {
            current = current->subset[0];
        }


        // count items and move to next leaf node

        while (current != nullptr)
        {
            count += current->data_count;

            current = current->next;
        }
    }

    return count;
}

template <typename T>
bool BPlusTree<T>::empty() const
{
    return data_count == 0;
}

template <typename T>
T* BPlusTree <T> :: find_ptr(const T &entry)
{
    if (!empty())
    {
        int i = first_ge(data, data_count, entry);

        if (is_leaf())
        {
            if (i < data_count && data[i] == entry)
            {
                return &data[i];
            }
        }

        else
        {
            if (i == data_count || entry < data[i])
            {
                return subset[i]->find_ptr(entry);
            }

            else
            {
                return subset[i + 1]->find_ptr(entry);
            }
        }
    }

    return nullptr;
}

template <typename T>
const T* BPlusTree<T> :: find_ptr(const T &entry) const
{
    if (!empty())
    {
        int i = first_ge(data, data_count, entry);

        if (is_leaf())
        {
            if (i < data_count && data[i] == entry)
            {
                return &data[i];
            }
        }

        else
        {
            if (i == data_count || entry < data[i])
            {
                return subset[i]->find_ptr(entry);
            }

            else
            {
                return subset[i + 1]->find_ptr(entry);
            }
        }
    }

    return nullptr;
}

template <typename T>
void BPlusTree <T> :: transfer_left(int i)
{
    //transfer one element LEFT from child i

    if (!subset[i]->is_leaf())
    {
        // move last in parent data to (i - 1) child's data

        attach_item(subset[i - 1]->data,
                subset[i - 1]->data_count, data[data_count - 1]);


        // remove first from i child's data

        T borrowed_item;

        delete_item(subset[i]->data, 0, subset[i]->data_count, borrowed_item);


        // overwrite last in parent data with first in i child

        data[data_count - 1] = borrowed_item;


        // remove borrowed item's child

        BPlusTree<T>* borrowed_child;

        delete_item(subset[i]->subset, 0,
                    subset[i]->child_count, borrowed_child);


        // add borrowed item's child to i - 1 child

        attach_item(subset[i - 1]->subset,
                subset[i - 1]->child_count, borrowed_child);
    }

    else
    {
        // remove first from i child's data

        T borrowed_item;

        delete_item(subset[i]->data, 0, subset[i]->data_count, borrowed_item);


        // transfer borrowed to i - 1 child

        attach_item(subset[i - 1]->data,
                subset[i - 1]->data_count, borrowed_item);


        // replace breadcrumb at i - 1 with first in i child

        data[i - 1] = subset[i]->data[0];
    }
}

template <typename T>
void BPlusTree <T> :: transfer_right(int i)
{
    //transfer one element RIGHT from child i

    if(!subset[i]->is_leaf())
    {
        // move first in parent data to (i + 1) child's data

        attach_item(subset[i + 1]->data, subset[i + 1]->data_count, data[0]);


        // remove last from i child's data

        T borrowed_item;

        detach_item(subset[i]->data, subset[i]->data_count, borrowed_item);


        // overwrite first in parent data with last in i child

        data[0] = borrowed_item;


        // remove borrowed item's child

        BPlusTree<T>* borrowed_child;

        detach_item(subset[i]->subset,
                    subset[i]->child_count, borrowed_child);


        // add borrowed item's child to i - 1 child

        insert_item(subset[i + 1]->subset, 0,
                subset[i + 1]->child_count, borrowed_child);
    }
    else
    {
        // remove last from i child's data
        T borrowed_item;

        delete_item(subset[i]->data, subset[i]->data_count - 1,
                    subset[i]->data_count, borrowed_item);


        // transfer borrowed to i + 1 child

        insert_item(subset[i + 1]->data, 0,
                subset[i + 1]->data_count, borrowed_item);


        // replace breadcrumb at i with transferred item

        data[i - 1] = borrowed_item;
    }
}

template <typename T>
BPlusTree <T>* BPlusTree <T> :: merge_with_next_subset(int i)
{
    //merge subset i with subset i+1

    BPlusTree<T>* merged_into = subset[i];

    BPlusTree<T>* source = subset[i + 1];

    if (!subset[i]->is_leaf())
    {
        // detach item i in parent's data

        T detached;

        delete_item(data, i, data_count, detached);



        // insert detached into merged_into

        attach_item(merged_into->data, merged_into->data_count, detached);



        // merge child i with i+1

        merge(merged_into->data, merged_into->data_count,
              source->data, source->data_count);



        // merge grandchildren manually (don't sort pointers)

        for (int i = 0; i < source->child_count; i++)
        {
            attach_item(merged_into->subset, merged_into->child_count,
                        source->subset[i]);
        }



        // remove child i+1, but first set child_count to 0
        //(don't delete previously held grandchildren)

        source->child_count = 0;

        BPlusTree<T>* discard_ptr;

        delete_item(subset, i + 1, child_count, discard_ptr);
    }

    else
    {
        // detach item i in parent's data

        T detached;

        delete_item(data, i, data_count, detached);


        // merge child i with i+1

        merge(merged_into->data, merged_into->data_count,
              source->data, source->data_count);


        // link child i with the one after child i+1

        merged_into->next = source->next;


        // remove child i+1

        BPlusTree<T>* discard_ptr;

        delete_item(subset, i + 1, child_count, discard_ptr);
    }

    delete source;

    return nullptr;
}

template <typename T>
void BPlusTree <T> :: remove_biggest(T &entry)
{
    //lol
}

template <typename T>
BPlusTree <T>* BPlusTree <T> :: fix_shortage(int i)
{
    //3 cases with application of left and right with merge

    if (i > 0 && subset[i - 1]->data_count > MINIMUM)
    {
        transfer_right(i - 1);
    }

    else if (i < child_count - 1 && subset[i + 1]->data_count > MINIMUM)
    {
        transfer_left(i + 1);
    }

    else if (i > 0)
    {
        merge_with_next_subset(i - 1);
    }

    else
    {
        merge_with_next_subset(i);
    }

    return subset[i];
}

template <typename T>
void BPlusTree <T> :: loose_remove(const T &entry)
{
    //allows MINIMUM-1 data elements in the root

    int i = first_ge(data, data_count, entry);

    if (is_leaf())
    {
        if (i != data_count && data[i] == entry)
        {
            T discarded;

            delete_item(data, i, data_count, discarded);
        }
    }

    else
    {
        int visit;

        if (i == data_count)
        {
            visit = i - 1;
        }

        else if (entry < data[i])
        {
            visit = i;
        }

        else
        {
            visit = i + 1;
        }

        subset[visit]->loose_remove(entry);

        // fix potential shortages

        if (subset[visit]->data_count < MINIMUM)
        {
            fix_shortage(visit);
        }

        // brute force fix breadcrumbs

        for (int i = 0; i < data_count; i++)
        {
            //print_array(data, data_count);

            //print_array(subset,child_count);

            //cout << "\nParent is: " << data[i] << endl;

            //cout << "\nRight child is: " << *subset[i + 1] << endl;

            subset[i + 1]->get_smallest(data[i]);

            //passing in data[i] and function modifies it turning it into
            //the lowest element

            //cout << "\nRight child is after fix is: " << *subset[i + 1] << endl;

            //cout << "\nParent after fix is: " << data[i] << endl;
        }
    }
}

template <typename T>
void BPlusTree <T> :: remove(const T &entry) //remove entry from the tree
{
    if (contains(entry))
    {
        loose_remove(entry);

        if (data_count == 0 && child_count > 0) // check if shrink needed
        {
            BPlusTree<T>* shrink_ptr = subset[0];

            // perform shallow copy

            copy_array(data, shrink_ptr->data,
                       data_count, shrink_ptr->data_count);

            copy_array(subset, shrink_ptr->subset,
                       child_count, shrink_ptr->child_count);


            shrink_ptr->data_count = 0;

            shrink_ptr->child_count = 0;

            delete shrink_ptr;
        }

        // brute force fix breadcrumbs

        for (int i = 0; i < data_count; i++)
        {
            if (subset[i + 1] != nullptr)
            {
                subset[i + 1]->get_smallest(data[i]);
            }
        }
    }
}

template <typename T>
bool BPlusTree <T> :: is_valid()
{
    // check array sizes

    if (data_count > MAXIMUM || child_count > MAXIMUM + 1)
    {
        cout << "Failed: data_count > MAXIMUM || child_count > MAXIMUM + 1"
             << endl;

        return false;
    }

    // check order of data items

    for (int i = 0; i < data_count - 1; i++)
    {
        if (data[i + 1] < data[i])
        {
            cout << "Failed: data[i + 1] < data[i]" << endl;

            return false;
        }
    }

    if (!is_leaf())
    {
        // check each child is also valid

        for (int i = 0; i < child_count; i++)
        {
            if (!subset[i]->is_valid())
            {
                cout << "Failed: !subset[i]->is_valid()" << endl;

                return false;
            }
        }

        // check orientation of each item with left/right child

        for (int i = 0; i < data_count; i++)
        {
            BPlusTree<T>* left_tree = subset[i];

            T largest_on_left_tree;

            left_tree->get_biggest(largest_on_left_tree);

            BPlusTree<T>* right_tree = subset[i + 1];

            T smallest_on_right_tree;

            right_tree->get_smallest(smallest_on_right_tree);

            T current = data[i];

            if (current < largest_on_left_tree
                    || smallest_on_right_tree != current)
            {
                cout << "Failed: current < largest_on_left_tree "
                        "|| smallest_on_right_tree < current" << endl;

                return false;
            }
        }
    }

    return true;
}


#endif // BTREE_H
