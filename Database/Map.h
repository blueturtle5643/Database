#ifndef MAP_H
#define MAP_H

#include "B+Tree.h"

using namespace std;

template <typename K, typename V>
struct Pair
{
    K key;

    V value;

    Pair(const K &k = K(), const V &v = V());

    friend ostream &operator<<(ostream &outs, const Pair<K, V> &print_me)
    {
        outs << print_me.key << ": " << print_me.value;

        return outs;
    }

    friend bool operator==(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    {
        return lhs.key == rhs.key;
    }

    friend bool operator<(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    {
        return lhs.key < rhs.key;
    }

    friend bool operator>(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    {
        return lhs.key > rhs.key;
    }

    friend bool operator<=(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    {
        return lhs < rhs || lhs == rhs;
    }

    friend Pair<K, V> operator+(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    {
        return rhs;
    }
};

template <typename K, typename V>
Pair<K, V> :: Pair(const K &k, const V &v) : key(k), value(v)
{

}

template <typename K, typename V>
class Map
{
    private:

        int key_count;

        BPlusTree<Pair<K, V>> map;

    public:

        typedef BPlusTree<Pair<K, V>> map_base;

        class Iterator
        {
            private:

                typename map_base :: Iterator _it;

            public:

                friend class Map;

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

                Pair<K, V> operator*()
                {
                    return *_it;
                }

                friend bool operator ==(const Iterator &lhs, const Iterator &
                                       rhs)
                {
                    return lhs._it == rhs._it;
                }

                friend bool operator !=(const Iterator &lhs, const Iterator &
                                       rhs)
                {
                    return lhs._it != rhs._it;
                }
            };

            Map();


            //  Iterators

            Iterator begin() const;

            Iterator end() const;


            //  Capacity

            int size() const;

            bool empty() const;


            //  Element Access

            V &operator[](const K &key);

            const V &operator[](const K &key) const;

            V &at(const K &key);

            const V &at(const K &key) const;


            //  Modifiers

            void insert(const K &k, const V &v);

            void erase(const K &key);

            void clear();

            V get(const K &key);


            //  Operations:

            Iterator find(const K &key);

            //Pair<K, V> *find(const K &key);

            bool contains(const Pair<K, V> &target) const;


            // I have not writtent hese yet, but we will need them:

            int count(const K &key) const;

            Iterator lower_bound(const K &key);

            Iterator upper_bound(const K &key);

            Pair<Iterator, Iterator> equal_range(const K &key);


            bool is_valid()
            {
                return map.is_valid();
            }

            friend ostream &operator<<(ostream &outs, const Map<K, V> &
                                       print_me)
            {
                outs << print_me.map << endl;

                return outs;
            }
};

template <typename K, typename V>
Map<K, V> :: Map() : key_count(0)
{

}

template <typename K, typename V>
int Map<K, V> :: size() const
{
    return key_count;
}

template <typename K, typename V>
bool Map<K, V> :: empty() const
{
    return size() == 0;
}

template <typename K, typename V>
V &Map<K, V> :: operator [](const K &key)
{
    Pair<K, V> temp(key, V());

    return map.get(temp).value;
}

template <typename K, typename V>
V &Map<K, V> :: at(const K &key)
{
    return this->operator[](key);
}

template <typename K, typename V>
const V &Map<K, V> :: at(const K &key) const
{
    return this->operator[](key);
}

template <typename K, typename V>
const V &Map<K, V> :: operator[](const K &key) const
{
    Pair<K, V> temp(key, V());

    return map.get(temp).value;
}

template <typename K, typename V>
void Map<K, V> :: insert(const K &k, const V &v)
{
    Pair<K, V> pair(k, v);

    if (map.contains(pair))
    {
        this->operator[](k) = v; // over-write existing value
    }

    else
    {
        map.insert(pair);

        key_count++;
    }
}

template <typename K, typename V>
void Map<K, V> :: erase(const K &key)
{
    Pair<K, V> temp(key, V());

    if (map.contains(temp))
    {
        map.remove(temp);

        key_count--;
    }
}

template <typename K, typename V>
void Map<K, V> :: clear()
{
    map.clear_tree();

    key_count = 0;
}

template <typename K, typename V>
V Map<K, V> :: get(const K &key)
{
    Pair<K, V> target(key, V());

    const Pair<K, V> pair = map.get(target);

    return pair.value;
}

//template <typename K, typename V>
//Pair <K, V> *Map <K, V> :: find(const K &key)
//{
//    Pair<K, V> target(key, V());

//    return map.find(target);
//}

template <typename K, typename V>
typename Map<K, V> :: Iterator Map<K, V> :: find(const K &key)
{
    Iterator it;

    it = map.find(key);

    return it;
}

template <typename K, typename V>
bool Map<K, V> :: contains(const Pair<K, V> &target) const
{
    return map.contains(target);
}

template <typename K, typename V>
int Map<K, V> :: count(const K &key) const
{
    Pair<K, V> target(key);

    if (contains(target))
    {
        return 1;
    }

    return 0;
}

template <typename K, typename V>
typename Map<K, V> :: Iterator Map<K, V> :: lower_bound(const K &key)
{
    Pair<K, V> target(key);

    return map.lower_bound(target);
}

template <typename K, typename V>
typename Map<K, V> :: Iterator Map<K, V> :: upper_bound(const K &key)
{
    Pair<K, V> target(key);

    return map.upper_bound(target);
}

template <typename K, typename V>
Pair<typename Map<K, V> :: Iterator, typename Map<K, V> :: Iterator>
Map<K, V> :: equal_range(const K &key)
{
    return Pair<typename Map<K, V> :: Iterator, typename Map<K, V> ::
            Iterator>(lower_bound(), upper_bound());
}

template <typename K, typename V>
typename Map<K, V> :: Iterator Map<K, V> :: begin() const
{
    return map.begin();
}

template <typename K, typename V>
typename Map<K, V> :: Iterator Map<K, V> :: end() const
{
    return map.end();
}

#endif // MAP_H
