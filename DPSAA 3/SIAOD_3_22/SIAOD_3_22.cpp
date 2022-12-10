#include <iostream>
#include "hashfile.h"
using namespace std;

void OutputBinFile(string pathToRead)
{
    ifstream fin(pathToRead, ios::in | ios::binary);
    Dictionary dict;

    if (fin.is_open())
    {
        while (fin.read((char*)&dict, sizeof(Dictionary)))
        {
            cout << dict.englishWord << " " << dict.russianWord << endl;
        }
    }
    else cout << "Файла с таким именем не существует" << endl;
    fin.close();
}


void print(Dictionary* dict, int size)
{
    for (size_t i = 0; i < size; i++)
    {
        cout << dict[i].englishWord << " " << dict[i].russianWord << " " << dict[i].noteNumber << endl;
    }
}

int main()
{
    system("chcp 1251 > null");

    string txt = "C:\\Users\\defox\\Desktop\\t.txt";
    string bin = "C:\\Users\\defox\\Desktop\\b.bin";

    convertTextToBin(txt, bin);
    OutputBinFile(bin);
    removeRecordFromBin(bin, 0);
    OutputBinFile(bin);
}