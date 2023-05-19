#ifndef MULTIMAP_H
#define MULTIMAP_H

#include <iostream>
#include <vector>

#include "B+Tree.h"

using namespace std;

template <typename T>
ostream &operator <<(ostream &outs, const vector<T> &values)
{
    for (int i = 0; i < values.size(); i++)
    {
        outs << values[i];

        if (i < values.size() - 1)
        {
            outs << ", ";
        }
    }

    return outs;
}

template <typename T>
void sort_values(vector<T> &values)
{
    for (int i = 0; i < values.size() - 1; i++) //bubblesort
    {
        for (int j = 0; j < values.size() - i - 1; j++)
        {
            if (values[j] > values[j + 1])
            {
                T temp = values[j];

                values[j] = values[j + 1];

                values[j + 1] = temp;
            }
        }
    }
}

template <typename T>
void remove_duplicate_values(vector<T> &values)
{
    for (int i = 0; i < values.size() - 1;)
    {
        if (values[i + 1] == values[i])
        {
            values.erase(values.begin() + i + 1);
        }

        else
        {
            i++;
        }
    }
}
template <typename T>
vector<T> vector_union(const vector<T> &lhs, const vector<T> &rhs)
{
    vector<T> result(lhs);

    result.insert(result.end(), rhs.begin(), rhs.end());

    sort_values(result);

    remove_duplicate_values(result);

    return result;
}

template <typename T>
vector<T> &operator +=(vector<T> &lhs, const vector<T> &rhs)
{
    lhs = vector_union(lhs, rhs);

    return lhs;
}

template <typename T>
vector<T> &operator +=(vector<T> &lhs, const T &rhs)
{
    lhs.push_back(rhs);

    return lhs;
}

template <typename K, typename V>
struct MultiPair
{
    K key;

    vector<V> values;

    MultiPair(const K &k = K());

    MultiPair(const K &k, const V &v);

    MultiPair(const K &k, const vector<V> &vlist);

    friend ostream &operator<<(ostream &outs, const MultiPair<K, V> &print_me)
    {
        outs << '[' << print_me.key << ": " << print_me.values << ']';

        return outs;
    }

    friend bool operator==(const MultiPair<K, V> &lhs,
                           const MultiPair<K, V> &rhs)
    {
        return lhs.key == rhs.key;
    }

    friend bool operator<(const MultiPair<K, V> &lhs,
                          const MultiPair<K, V> &rhs)
    {
        return lhs.key < rhs.key;
    }

    friend bool operator>(const MultiPair<K, V> &lhs,
                          const MultiPair<K, V> &rhs)
    {
        return lhs.key > rhs.key;
    }

    friend bool operator<=(const MultiPair<K, V> &lhs,
                           const MultiPair<K, V> &rhs)
    {
        return lhs < rhs || lhs == rhs;
    }

    friend MultiPair<K, V> operator+(const MultiPair<K, V> &lhs,
                                     const MultiPair<K, V>
                                         &rhs)
    {
        vector<V> temp = vector_union(lhs.values, rhs.values);

        return MultiPair<K, V>(lhs.key, temp);
    }
};

template <typename K, typename V>
MultiPair<K, V> :: MultiPair(const K &k) : key(k)
{

}

template <typename K, typename V>
MultiPair<K, V> :: MultiPair(const K &k, const V &v) : key(k),
                                                     values(vector<V>(1, v))
{

}

template <typename K, typename V>
MultiPair<K, V> :: MultiPair(const K &k, const vector<V> &vlist)
    : key(k), values(vlist)
{

}

template <typename K, typename V>
class MultiMap
{
private:

    BPlusTree<MultiPair<K, V>> multimap;

public:

    typedef BPlusTree<MultiPair<K, V>> map_base;

    class Iterator
    {
    private:

        typename map_base :: Iterator _it;

    public:

        friend class MultiMap;

        Iterator(typename map_base :: Iterator it) : _it(it)
        {

        }

        Iterator operator++(int unused)
        {
            return _it++;
        }

        Iterator operator++()
        {
            return ++_it;
        }

        MultiPair<K, V> operator*()
        {
            return *_it;
        }

        friend bool operator==(const Iterator &lhs,
                               const Iterator &rhs)
        {
            return lhs._it == rhs._it;
        }

        friend bool operator!=(const Iterator &lhs,
                               const Iterator &rhs)
        {
            return lhs._it != rhs._it;
        }
    };


    // Iterators

    Iterator begin();

    Iterator end();


    MultiMap();


    // Capacity

    int size() const;

    bool empty() const;


    // Element Access

    const vector<V> &operator[](const K &key) const;

    vector<V> &operator[](const K &key);


    // Modifiers

    void insert(const K &k, const V &v);

    void erase(const K &key);

    void clear();


    // Operations

    bool contains(const K &key) const;

    const vector<V> &get(const K &key) const;

    Iterator find(const K &key);


    //MultiPair<K, V> *find(const K &key);

    int count(const K &key) const;

    Iterator lower_bound(const K &key);

    Iterator upper_bound(const K &key);

    MultiPair<Iterator, Iterator> equal_range(const K &key);


    bool is_valid()
    {
        return multimap.is_valid();
    }

    friend ostream &operator<<(ostream &outs,
                               const MultiMap<K, V> &print_me)
    {
        outs << print_me.multimap << endl;

        return outs;
    }
};

template <typename K, typename V>
MultiMap<K, V> :: MultiMap()
{

}

template <typename K, typename V>
int MultiMap<K, V> :: size() const
{
    int count = 0;

    for (MultiMap<K, V> :: Iterator it =
         multimap.begin(); it != multimap.end(); ++it)
    {
        count += it->values.size();
    }
    return count;
}

template <typename K, typename V>
bool MultiMap<K, V> :: empty() const
{
    return size() == 0;
}

template <typename K, typename V>
vector<V> &MultiMap<K, V> :: operator [](const K &key)
{
    MultiPair<K, V> temp(key);

    return multimap.get(temp).values;
}

template <typename K, typename V>
const vector<V> &MultiMap<K, V> :: operator [](const K &key) const
{
    MultiPair<K, V> temp(key, V());

    return multimap.get(temp).values;
}

template <typename K, typename V>
void MultiMap<K, V> :: insert(const K &k, const V &v)
{
    MultiPair<K, V> MultiPair(k, v);

    if (multimap.contains(MultiPair))
    {
        this->operator[](k) += v; // appends to existing values
    }

    else
    {
        multimap.insert(MultiPair);
    }
}

template <typename K, typename V>
void MultiMap<K, V> :: erase(const K &key)
{
    MultiPair<K, V> temp(key, V());

    if (multimap.contains(temp))
    {
        multimap.remove(temp);
    }
}

template <typename K, typename V>
void MultiMap<K, V> :: clear()
{
    multimap.clear_tree();
}

template <typename K, typename V>
const vector<V> &MultiMap<K, V> :: get(const K &key) const
{
    MultiPair<K, V> target(key);

    return multimap.get(target).values;
}

template <typename K, typename V>
typename MultiMap<K, V> :: Iterator MultiMap<K, V> :: find(const K &key)
{
    return multimap.find(key);
}

template <typename K, typename V>
bool MultiMap<K, V> :: contains(const K &key) const
{
    MultiPair<K, V> target(key);

    return multimap.contains(target);
}

template <typename K, typename V>
int MultiMap<K, V> :: count(const K &key) const
{
    MultiPair<K, V> target(key);

    return multimap.get(target).values.size();
}

template <typename K, typename V>
typename MultiMap<K, V> :: Iterator MultiMap<K, V> :: lower_bound(const K &key)
{
    MultiPair<K, V> target(key);

    return multimap.lower_bound(target);
}

template <typename K, typename V>
typename MultiMap<K, V> :: Iterator MultiMap<K, V> :: upper_bound(const K &key)
{
    MultiPair<K, V> target(key);

    return multimap.upper_bound(target);
}

template <typename K, typename V>
MultiPair<typename MultiMap<K, V> :: Iterator,
typename MultiMap<K, V> :: Iterator>
MultiMap<K, V> :: equal_range(const K &key)
{
    return MultiPair<typename MultiMap<K, V> :: Iterator,
                     typename MultiMap<K, V> :: Iterator>
            (lower_bound(), upper_bound());
}

template <typename K, typename V>
typename MultiMap<K, V> :: Iterator MultiMap<K, V> :: begin()
{
    return multimap.begin();
}

template <typename K, typename V>
typename MultiMap<K, V> :: Iterator MultiMap<K, V> :: end()
{
    return multimap.end();
}

#endif // MULTIMAP_H
