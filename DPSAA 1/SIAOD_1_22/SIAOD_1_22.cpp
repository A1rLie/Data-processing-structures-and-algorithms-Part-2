#include <iostream>
#include <string>

using namespace std;

string ConvertIntToBinaryString(unsigned int number)
{
    string resultNumber = "";

    while (number > 0)
    {
        resultNumber = to_string(number % 2) + resultNumber;
        number /= 2;
    }

    int countBits = resultNumber.size();

    for (int i = 0; i < 32 - countBits; i++)
    {
        resultNumber = "0" + resultNumber;
    }

    return resultNumber;
}

int Task1(unsigned int mask, unsigned int num)
{
    return mask | num;
}

int Task2(unsigned int mask, int num)
{
    return mask & num;
}

int Task3(int number)
{
    return number << 4;
}

int Task4(int number)
{
    return number >> 4;
}

int Task5(int number, int binIndex)
{
    return number >> (31 - binIndex);
}

int main()
{
    system("chcp 1251 > null");

    const unsigned int NUMBER1 = 0xFF;
    const unsigned int NUMBER2 = 0xF0;
    unsigned int MASK1 = 0xF;
    unsigned int userNum;

    //Task #1
    cout << "Task #1\n";
    cout << "hex numb: " << hex << NUMBER1 << ", bin numb: " << ConvertIntToBinaryString(NUMBER1) << endl;
    cout << "hex mask: " << hex << MASK1 << " , bin mask: " << ConvertIntToBinaryString(MASK1) << endl;
    cout << "hex res:  " << hex << Task1(MASK1, NUMBER1) << ", bin res:  " << ConvertIntToBinaryString(Task1(MASK1, NUMBER1)) << endl;
    cout << "---------------------------------" << endl;
    cout << "hex numb: " << hex << NUMBER2 << ", bin numb: " << ConvertIntToBinaryString(NUMBER2) << endl;
    cout << "hex mask: " << hex << MASK1 << " , bin mask: " << ConvertIntToBinaryString(MASK1) << endl;
    cout << "hex res:  " << hex << Task1(MASK1, NUMBER2) << ", bin res:  " << ConvertIntToBinaryString(Task1(MASK1, NUMBER2)) << endl;


    //Task #2
    cout << "\nTask #2\n";
    const unsigned int MASK2 = 0xBEB;
    cout << "Введите число >> ";
    cin >> userNum;
    cout << "hex numb: " << hex << userNum << ", bin numb: " << ConvertIntToBinaryString(userNum) << endl;
    cout << "hex mask: " << hex << MASK2 << " , bin mask: " << ConvertIntToBinaryString(MASK2) << endl;
    cout << "hex res:  " << hex << Task2(MASK2, userNum) << ", bin res:  " << ConvertIntToBinaryString(Task2(MASK2, userNum)) << endl;

    //Task #3
    cout << "\nTask #3\n";
    cout << "Введите число для умножения на 16 >> ";
    cin >> userNum;
    userNum = Task3(userNum);
    cout << dec << "dec: " << userNum << ", bin " << ConvertIntToBinaryString(userNum) << endl;

    //Task #4
    cout << "\nTask #4\n";
    cout << "Введите число для деления на 16 >> ";
    cin >> userNum;
    userNum = Task4(userNum);
    cout << dec << "dec: " << userNum << ", bin: " << ConvertIntToBinaryString(userNum) << endl;

    //Task #5
    cout << dec << "\nTask #5\n";
    const unsigned int MASK3 = 0x80000000;

    unsigned int binNumber;
    cout << "Введите число и позицию бита >> ";
    cin >> userNum >> binNumber;
    userNum = Task5(userNum, binNumber);

    cout << "Число: " << userNum << ", bin: " << ConvertIntToBinaryString(userNum) << endl;
    cout << "Маска: " << MASK3 << ", bin: " << ConvertIntToBinaryString(MASK3) << endl;
    cout << "Результат: " << Task1(MASK3, userNum) << ", bin: " << ConvertIntToBinaryString(Task1(MASK3, userNum)) << endl;
}
