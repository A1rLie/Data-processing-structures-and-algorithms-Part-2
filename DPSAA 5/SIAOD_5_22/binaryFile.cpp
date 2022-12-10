#include "binaryFile.h"

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

bool searchAndPrintDictionary(string path, char key[10])
{
    ifstream fin;
    fin.open(path, ios::binary | ios::in);
    Dictionary dict;
    if (fin.is_open())
    {
        while (fin.read((char*)&dict, sizeof(Dictionary)))
        {
            if (strcmp(dict.englishWord, key) == 0)
            {
                cout << "English: " << dict.englishWord << "; russian: " << dict.russianWord << endl;
                fin.close();
                return true;
            }
        }
        fin.close();
    }
    return false;
}

bool getAndPrintDictionary(string path, int index)
{
    ifstream fin;
    fin.open(path, ios::binary | ios::in);
    if (fin.is_open())
    {
        if (!isLess(path, index)) return false;
        Dictionary dict;
        fin.seekg(index * sizeof(Dictionary), ios::beg);
        fin.read((char*)&dict, sizeof(Dictionary));
        cout << "English: " << dict.englishWord << "; russian: " << dict.russianWord << endl;
        fin.close();
        return true;
    }
    return false;
}

bool addDictionary(string path, Dictionary dict, int& index)
{
    fstream fout;
    fout.open(path, ios::binary | ios::in | ios::out);
    if (fout.is_open())
    {
        while (isLess(path, index)) index++;
        fout.seekg(0, ios::end);
        fout.write((char*)&dict, sizeof(Dictionary));
        return true;
    }
    else return false;
}