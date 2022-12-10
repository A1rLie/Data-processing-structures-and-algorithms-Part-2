#include "file.h"

bool convertTextToBin(string pathToRead, string pathToWrite)
{
    ifstream fin(pathToRead, ios::in);

    if (fin.is_open())
    {
        ofstream fout(pathToWrite, ios::out | ios::binary);
        Dictionary dict;
        while (!fin.eof())
        {
            fin >> dict.englishWord >> dict.russianWord;
            fout.write((char*)&dict, sizeof(Dictionary));
        }
        fout.close();
        return true;
    }
    else return false;
}

bool isLess(string path, int index)
{
    ifstream fin;
    fin.open(path, ios::binary | ios::in);

    Dictionary temp;
    int count = 0;
    while (fin.read((char*)&temp, sizeof(Dictionary)))
    {
        count++;
    }
    fin.close();
    if (count > index) return true;
    else return false;

}

bool removeRecordFromBin(string path, int index)
{
    fstream fout;
    fout.open(path, ios::binary | ios::in | ios::out);
    if (fout.is_open())
    {
        Dictionary dict;
        Dictionary empty;

        if (!isLess(path, index)) return false;

        fout.seekg((index) * sizeof(Dictionary), ios::beg);
        fout.write((char*)&dict, sizeof(Dictionary));

        return true;
    }
    else return false;

}

Dictionary getRecordFromBin(string path, int index)
{
    ifstream fin;
    fin.open(path, ios::binary | ios::in);
    Dictionary result;

    if (fin.is_open())
    {
        if (!isLess(path, index)) return result;
        Dictionary dict;
        fin.seekg(index * sizeof(Dictionary), ios::beg);
        fin.read((char*)&dict, sizeof(Dictionary));
        result = dict;
    }
    return result;
    fin.close();

}

//Useless func
bool addRecordToBin(string path, Dictionary dict)
{
    fstream fout;
    fout.open(path, ios::binary | ios::in | ios::out);
    if (fout.is_open())
    {
        fout.seekg(0, ios::end);
        fout.write((char*)&dict, sizeof(Dictionary));

        return true;
    }
    else return false;
}
