#ifndef ARRAY_UTILITY_H
#define ARRAY_UTILITY_H

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
T maximal(const T &a, const T &b); //return the larger of the two items

template <typename T>
void swaperino(T &a, T &b); //swap the two items

template <typename T>
int index_of_maximal(T data[], int n); //return index of the largest item in data

template <typename T>
void ordered_insert(T data[], int &n, T entry); //insert entry into the sorted array
//data with length n

template <typename T>
int first_ge(const T data[], int n, const T &entry); //return the first element in data that is
//not less than entry

template <typename T>
void attach_item(T data[], int &n, const T &entry); //append entry to the right of data

template <typename T>
void insert_item(T data[], int i, int &n, T entry); //insert entry at index i in data

template <typename T>
void detach_item(T data[], int &n, T &entry); //remove the last element in data and place
//it in entry

template <typename T>
void delete_item(T data[], int i, int &n, T &entry); //delete item at index i and place it in entry

template <typename T>
void merge(T data1[], int &n1, T data2[], int &n2); //append data2 to the right of data1

template <typename T>
void split(T data1[], int &n1, T data2[], int &n2); //move n/2 elements from the right of data1
//and move to data2

template <typename T>
void copy_array(T dest[], const T src[],
                int &dest_size, int src_size); //copy src[] into dest[]

template <typename T>
void print_array(const T data[], int n, int pos = -1); //print array data

template <typename T>
bool is_gt(const T data[], int n, const T &item); //item > all data[i]

template <typename T>
bool is_le(const T data[], int n, const T &item); //item <= all data[i]

//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream &operator<<(ostream &outs, const vector<T> &list); //print vector list

template <typename T>
vector<T> &operator+=(vector<T> &list, const T &addme); //list.push_back addme

template <typename T>
T maximal(const T &a, const T &b)
{
    if (a > b)
    {
        return a;
    }

    return b;
}

template <typename T>
void swaperino(T &a, T &b)
{
    T temp = a;

    a = b;

    b = temp;
}

template <typename T>
int index_of_maximal(T data[], int n)
{
    int max_index = 0;

    for (int i = 1; i < n; i++)
    {
        if (data[max_index] < data[i])
        {
            max_index = i;
        }
    }

    return max_index;
}

template <typename T>
void ordered_insert(T data[], int &n, T entry)
{
    insert_item(data, first_ge(data, n, entry), n, entry);
}

template <typename T>
int first_ge(const T data[], int n, const T &entry)
{
    if (n > 0 && data[n - 1] < entry) //if entry is larger than last element return size
    {
        return n;
    }

    for (int i = 0; i < n; i++)
    {
        if (entry < data[i] || entry == data[i]) //if entry is less than or equal to index item
        {
            return i;
        }
    }

    return n;
}

template <typename T>
void attach_item(T data[], int &n, const T &entry) //IMPORTANT: N is size not capacity
{
    data[n] = entry;

    n++;
}

template <typename T>
void insert_item(T data[], int i, int &n, T entry)
{
    for (int index = n - 1; index >= i; index--)
    {
        data[index + 1] = data[index];
    }

    data[i] = entry;

    n++;
}

template <typename T>
void detach_item(T data[], int &n, T &entry)
{
    entry = data[n - 1];

    n--;
}

template <typename T>
void delete_item(T data[], int i, int &n, T &entry)
{
    entry = data[i];

    for (int index = i + 1; index < n; index++)
    {
        data[index - 1] = data[index];
    }

    n--;
}

template <typename T>
void merge(T data1[], int &n1, T data2[], int &n2)
{
    for (int i = 0; i < n2; i++)
    {
        ordered_insert(data1, n1, data2[i]);
    }
}

template <typename T>
void split(T data1[], int &n1, T data2[], int &n2)
{
    for (int i = n1 / 2, j = 0; i < n1; i++, j++)
    {
        data2[j] = data1[i];
    }

    if (n1 % 2 == 1)
    {
        n2 = n1 / 2 + 1;
    }

    else
    {
        n2 = n1 / 2;
    }

    n1 /= 2;
}

template <typename T>
void copy_array(T dest[], const T src[],
                int &dest_size, int src_size)
{
    int i = 0;

    while (i != src_size)
    {
        dest[i] = src[i];

        i++;
    }

    dest_size = src_size;
}

template <typename T>
void print_array(const T data[], int n, int pos)
{
    cout << endl;

    for (int i = 0; i < n; i++)
    {
        cout << "[" << data[i] << "]";
    }

    cout << endl;
}

template <typename T>
bool is_gt(const T data[], int n, const T &item)
{
    return data[n - 1] < item;
}

template <typename T>
bool is_le(const T data[], int n, const T &item)
{
    return item < data[0] || item == data[0];
}

#endif // ARRAY_UTILITY_H
