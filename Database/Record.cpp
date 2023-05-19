#include "Record.h"

Record :: Record() : recno(-1), _num_of_fields(0)
{
}

Record :: Record(const vectorstr &v) : recno(-1), _num_of_fields(v.size())
{
    for (int i = 0; i < v.size(); i++)
    {
        strcpy(_record[i], v[i].c_str());
    }
}

vectorstr Record :: get_record() const
{
    //strncpy(_record, s.c_str(), MAX);

    vectorstr v;

    //cout << "\nGet_record(): " << _num_of_fields << endl;

    for (int i = 0; i < _num_of_fields; i++)
    {
        v.push_back(string(_record[i]));
    }

    return v;
}

long Record :: write(fstream &outs) //returns the record number
{

    //write to the end of the file.

    outs.seekg(0, outs.end);

    long pos = outs.tellp(); //retrieves the current position of the
    //      file pointer

    //outs.write(&record[0], sizeof(record));

    //outs.write(_record, sizeof(_record));

    outs.write(&_record[0][0], sizeof(_record));

    return pos / sizeof(_record); //record number
}

long Record :: read(fstream &ins, long recno)
{
    long pos = recno * sizeof(_record);

    ins.seekg(pos, ios_base::beg);

    //ins.read(_record, sizeof(_record));

    clear_record();

    ins.read(&_record[0][0], sizeof(_record));


    // update other member variables according contents read from file

    this->recno = recno;

    _num_of_fields = 0;

    while (_num_of_fields < MAX_ROWS && _record[_num_of_fields][0] != '\0')
    {
        _num_of_fields++;
    }

    //don't you want to mark the end of  the cstring with null?
    //_record[] => [zero'\0'trash trash trash trash]
    //don't need the null character, but for those of us with OCD and PTSD:

    //_record[ins.gcount()] = '\0';

    return ins.gcount();
}

void Record :: clear_record()
{
    if (_record[0][0] != '\0') // if there is something on the first row
    {
        for (int i = 0; i < MAX_ROWS; i++)
        {
            for (int j = 0; j < MAX_COLS; j++)
            {
                _record[i][j] = '\0';
            }
        }
    }
}

ostream &operator <<(ostream &outs, const Record &r)
{
    //outs<<r._record;

    for (int i = 0; i < r._num_of_fields; i++)
    {
        outs << r._record[i] << "|";
    }

    return outs;
}

bool file_exists(const char filename[])
{
    const bool debug = false;

    fstream ff;

    ff.open(filename, std::fstream::in | std::fstream::binary);

    if (ff.fail())
    {
        if (debug)
        {
            cout << "\nFile_exists(): File does NOT exist: " << filename << endl;
        }

        return false;
    }

    if (debug)
    {
        cout << "\nFile_exists(): File DOES exist: " << filename << endl;
    }

    ff.close();

    return true;
}

void open_fileRW(fstream &f, const char filename[]) throw(char *)
{
    const bool debug = false;

    //openning a nonexistent file for in|out|app causes a fail()
    //  so, if the file does not exist, create it by openning it for
    //  output:

    if (!file_exists(filename))
    {
        //create the file

        f.open(filename, std::fstream::out | std::fstream::binary);

        if (f.fail())
        {
            cout << "\nFile open (RW) failed: With out [" << filename << "]"
                 << endl;

            throw("\nFile RW failed.\n");
        }

        else
        {
            if (debug)
            {
                cout << "\nOpen_file RW: File created successfully: "
                     << filename << endl;
            }
        }
    }

    else
    {
        f.open(filename, std::fstream::in | std::fstream::out |
               std::fstream::binary);

        if (f.fail())
        {
            cout << "\nFile open (RW) failed. [" << filename << "]" << endl;

            throw("\nFile failed to open.\n");
        }
    }
}

void open_fileW(fstream &f, const char filename[])
{
    f.open(filename, std::fstream::out | std::fstream::binary);

    if (f.fail())
    {
        cout << "\nFile open failed: " << filename << endl;

        throw("\nFile failed to open.\n");
    }
}
