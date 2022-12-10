#include <iostream>
#include <fstream>
#include <time.h>
#include <string>

using namespace std;

struct EngRuDictionary
{
    char englishWord[10] = "";
    char russianWord[10] = "";
};


void ConvertTextToBin(string pathToWrite, string pathToRead)
{
    ifstream fin(pathToRead, ios::in);

    if (fin.is_open())
    {
        ofstream fout(pathToWrite, ios::out | ios::binary);
        EngRuDictionary dict;
        while (!fin.eof())
        {
            fin >> dict.englishWord >> dict.russianWord;
            fout.write((char*)&dict, sizeof(EngRuDictionary));
        }
        fout.close();
    }
    else cout << "Файла с таким именем не существует" << endl;
    
    fin.close();
}

void ConvertBinToText(string pathToRead, string pathToWrite)
{
    ifstream fin;
    fin.open(pathToRead, ios::binary|ios::in);

    if (fin.is_open())
    {
        ofstream fout;
        fout.open(pathToWrite, ios::out);
        EngRuDictionary dict;
        while (fin.read((char*)&dict, sizeof(EngRuDictionary)))
        {
            fout << dict.englishWord << " " << dict.russianWord << "\n";
        }
        fout.close();
    }
    else cout << "Файла с таким именем не существует" << endl;
    fin.close();
}

void OutputBinFile(string pathToRead)
{
    ifstream fin(pathToRead, ios::in|ios::binary);
    EngRuDictionary dict;

    if (fin.is_open())
    {
        while (fin.read((char*)&dict, sizeof(EngRuDictionary)))
        {
            cout << dict.englishWord << " " << dict.russianWord << endl;
        }
    }
    else cout << "Файла с таким именем не существует" << endl;
    fin.close();
}

bool IsLess(string pathToRead, int index)
{
    ifstream fin;
    fin.open(pathToRead, ios::binary|ios::in);

    EngRuDictionary temp;
    int count = 0;
    while (fin.read((char*)&temp, sizeof(EngRuDictionary)))
    {
        count++;
    }
    fin.close();
    if (count > index) return true;
    else return false;
}

string GetDictionary(string pathToRead, int index)
{
    ifstream fin;
    fin.open(pathToRead, ios::binary|ios::in);
    string result = "";

    if (fin.is_open())
    {
        if (!IsLess(pathToRead, index)) return "Индекс превосходит количество элементов";
        EngRuDictionary dict;
        fin.seekg(index * sizeof(EngRuDictionary), ios::beg);
        fin.read((char*)&dict, sizeof(EngRuDictionary));
        result = dict.englishWord;
        result += " ";
        result += dict.russianWord;
    }
    else result = "Файла с таким именем не существует";
    return result;
    fin.close();
}

void RemoveState(string path, int index)
{
    fstream fout;
    fout.open(path, ios::binary|ios::in|ios::out);
    if (fout.is_open())
    {
        EngRuDictionary dict;
        EngRuDictionary empty;

        if (!IsLess(path, index))
        {
            cout << "Индекс превышает количество записей" << endl;
            return;
        }

        fout.seekg(-1 * sizeof(EngRuDictionary), ios::end);
        fout.read((char*)&dict, sizeof(EngRuDictionary));

        fout.seekg(-1 * sizeof(EngRuDictionary), ios::cur);
        fout.write((char*)&empty, sizeof(EngRuDictionary));

        fout.seekg((index) * sizeof(EngRuDictionary), ios::beg);
        fout.write((char*)&dict, sizeof(EngRuDictionary));
    }
    else cout << "Файла с таким именем не существует" << endl;
}

void ShowWords(string pathToRead, char symb)
{
    ifstream fin;
    fin.open(pathToRead, ios::in);

    EngRuDictionary dict;
    if (fin.is_open())
    {
        while (fin.read((char*)&dict, sizeof(EngRuDictionary)))
        {
            if (dict.englishWord[0] == symb)
            {
                cout << dict.englishWord << " " << dict.russianWord << endl;
            }
        }
    }
    else cout << "Файла с таким именем не существует" << endl;
}

void EditTranslate(string path, string oldWord, string newWord)
{
    fstream fiot;
    fiot.open(path, ios::binary | ios::out | ios::in);
    if (fiot.is_open())
    {
        EngRuDictionary dict;
        while (fiot.read((char*)&dict, sizeof(EngRuDictionary)))
        {
            if (dict.russianWord == oldWord)
            {
                for (int i = 0; i < (newWord.length() < 10 ? newWord.length() : 10); i++)
                {
                    dict.russianWord[i] = newWord[i];
                }
                fiot.seekg(-1 * sizeof(EngRuDictionary), ios::cur);
                fiot.write((char*)&dict, sizeof(EngRuDictionary));
                break;
            }
        }
    }
    else cout << "Файла с таким именем не существует" << endl;
}
int main()
{
    system("chcp 1251 > null");
    srand(time(NULL));

    int task;
    string fileNameBin;

    while (true)
    {
        cout << "1. Преобразование тестовых данных из текстового файла в двоичный файл\n" <<
            "2. Преобразование данных из двоичного файла в текстовый\n" <<
            "3. Вывод всех записей двоичного файла\n" <<
            "4. Доступ к записи по ее порядковому номеру в файле, используя механизм прямого доступа к записи в двоичном файле\n" <<
            "5. Удаление записи с заданным значением ключа, выполнить путем замены на последнюю запись\n" <<
            "6. Сформировать список английских слов, начинающихся с указанной буквы и их русский перевод\n" <<
            "7. Обновить запись, записав новый вариант русского перевода по заданному слову\n" << 
            ">> ";
        cin >> task;
        cout << "Введите имя бинарного файла >> ";
        cin >> fileNameBin;
        cin.ignore();
        cin.clear();

        switch (task)
        {
        case 1:
        {
            string fileNameTxt;
            cout << "Введите имя текстового файла для копирования в двоичный >> ";
            cin >> fileNameTxt;
            ConvertTextToBin(fileNameBin, fileNameTxt);
            break;
        }
        case 2:
        {
            string fileNameTxt;
            cout << "Введите имя текстового файла для копирования из двоичного >> ";
            cin >> fileNameTxt;
            ConvertBinToText(fileNameBin, fileNameTxt);
            break;
        }
        case 3:
        {
            OutputBinFile(fileNameBin);
            break;
        }
        case 4:
        {
            int index;
            cout << "Введите индекс интересуещего элемента >> ";
            cin >> index;
            cout << GetDictionary(fileNameBin, index) << endl;
            break;
        }
        case 5:
        {
            int index;
            cout << "Введите индекс интересуещего элемента >> ";
            cin >> index;
            RemoveState(fileNameBin, index);
            break;
        }
        case 6:
        {
            char firstSymb;
            cout << "Введите первый символ английских слов >> ";
            cin >> firstSymb;
            ShowWords(fileNameBin, firstSymb);
            break;
        }
        case 7:
        {
            string oldWord;
            cout << "Введите русское слово на замену >> ";
            cin >> oldWord;
            string newWord;
            cout << "Введите слово для замены >> ";
            cin >> newWord;
            EditTranslate(fileNameBin, oldWord, newWord);
            
            break;
        }

        default:
            cout << "Выход из программы" << endl;
            return 1;
            break;
        }
        cout << endl;
    }
}
