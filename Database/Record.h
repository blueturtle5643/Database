#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

bool file_exists(const char filename[]);

void open_fileRW(fstream &f, const char filename[]) throw(char *);

void open_fileW(fstream &f, const char filename[]);

typedef vector<string> vectorstr;
class Record
{
    private:
        static const int MAX_ROWS = 20;

        static const int MAX_COLS = 50;

        int recno;

        int _num_of_fields;

        char _record[MAX_ROWS][MAX_COLS] = {0};

        void clear_record();

    public:
        //when you construct a Record, it's either empty or it
        //  contains a word
        Record();

        Record(const vectorstr &v);

        vectorstr get_record() const;

        long write(fstream &outs); //returns the record number

        //returns the number of bytes
        //      read = MAX, or zero if
        //      read passed the end of file
        long read(fstream &ins, long recno);

        friend ostream &operator<<(ostream &outs, const Record &r);
};

/*
template <typename T>
ostream &operator<<(ostream &outs, const vector<T> &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        outs << v[i] << " ";
    }

    return outs;
}
*/

#endif // RECORD_H
