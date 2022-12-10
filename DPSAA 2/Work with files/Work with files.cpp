#include <iostream>
#include <fstream>
#include <time.h>
#include <string>

using namespace std;

void CreateAndFillFile(string path)
{
    ofstream fout;
    fout.open(path, ios::out);

    int lines = rand() % 10 + 1;
    for (int i = 0; i < lines; i++)
    {
        int countNumbers = rand() % 6 + 1;
        for (int j = 0; j < countNumbers; j++)
        {
            fout << rand() % 20 + 1 << " ";
        }
        if (i < lines - 1) fout << endl;
    }
    if (fout.good()) fout.close();
    else return;
}

void PrintFile(string path)
{
    ifstream fin;
    fin.open(path, ios::in);
    if (fin.is_open())
    {
        string line;
        while (!fin.eof())
        {
            getline(fin, line);
            cout << line << endl;
        }
    }
    else cout << "Файла с таким именем не существует" << endl;
    if (fin.good()) fin.close();
    else return;
}

void AppendLine(string path, string line)
{
    ofstream fout;
    fout.open(path, ios::app);
    fout << endl << line;
    if (fout.good()) fout.close();
    else return;
}

int GetNumber(string path, int numberIndex)
{
    int resultNumber = INT32_MIN;
    ifstream fin;
    fin.open(path, ios::in);
    if (fin.is_open())
    {
        for (int i = 0; i <= numberIndex; i++)
        {
            fin >> resultNumber;
        }
    }
    else cout << "Файла с таким именем не существует" << endl;
    if (fin.good()) fin.close();
    else return 0;

    return resultNumber;
}

int CountNumbers(string path)
{
    int count = 0;  
    string trash;

    ifstream fin;
    fin.open(path, ios::in);
    if (fin.is_open())
    {
        while (!fin.eof())
        {
            fin >> trash;
            count++;
        }

    }
    else cout << "Файла с таким именем не существует" << endl;
    if (fin.good()) fin.close();

    return count;
}

void AdditionalTask(string path)
{
    ifstream fin;
    fin.open(path, ios::in);
    if (fin.is_open())
    {
        int maxNumber = 1;
        int tempNumber;
        while (fin >> tempNumber)
        {
            if (tempNumber > maxNumber) maxNumber = tempNumber;
        }
        fin.close();

        ofstream fout;
        fout.open("newFile.txt", ios::out);
        fin.open(path, ios::in);

        while (fin >> tempNumber)
        {
            fout << tempNumber * maxNumber << " ";
        }

        if (fin.good() && fout.good())
        {
            fout.close();
            fin.close();
        }
        else return;
    }
    else cout << "Файла с таким именем не существует" << endl;
    fin.close();
}

int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(NULL));
   
    int task;
    string fileName;
    
    while (true)
    {
        cout << "1. Cоздание текстового файла кодировки ASCII, содержащего десятичные числа по несколько чисел на строке\n" <<
            "2. Вывод содержимого текстового файла\n" <<
            "3. Добавление новой строки в конец файла\n" <<
            "4. Прочитать значение числа, указав его порядковый номер в файле, и вернуть его значение\n" <<
            "5. Определить количество чисел в файле\n" <<
            "6. Создать новый файл из значений исходного, умножив каждое четное число на максимальное число в файле\n" << 
            ">> ";
        cin >> task;
        cout << "Имя файла >> ";
        cin >> fileName;
        cin.ignore();
        cin.clear();

        switch (task)
        {
        case 1:
        {
            CreateAndFillFile(fileName);
            break;
        }
        case 2:
        {
            PrintFile(fileName);
            break;
        }
        case 3:
        {
            string lineToAppend;
            cout << "Введите строку для добавления >> ";
            getline(cin,lineToAppend);
            AppendLine(fileName, lineToAppend);
            break;
        }
        case 4:
        {
            int numberIndex;
            cout << "Номер желаемого числа, начиная с 0 >> ";
            cin >> numberIndex;
            
            int result = GetNumber(fileName, numberIndex);
            cout << "Число под требуемым индексом: " << result << endl;
            break;
        }
        case 5:
        {
            int count = CountNumbers(fileName);
            cout << "Количество чисел: " << count << endl;
            break;
        }
        case 6:
        {
            AdditionalTask(fileName);
            break;
        }
        default:
            cout << "Задание не выбрано\nВыход из программы..." << endl;
            return 1;
        }
        cout << endl;
    }
}
