#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
    system("chcp 1251 > null");
    Graph cities;
    int choice;
    while (true)
    {
        cout << "1. ���������� ������\n2. ����� ����� ����� �������\n3. ����������� �����\n>> ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            int first, second, weight;
            cout << "������� ����� ������� ������, ������� � ������������� ������ ����� ���� >> ";
            cin >> first >> second >> weight;
            if (cities.add(first, second, weight) == false) cout << "������� ����� ������� � ������������!";
            break;
        }
        case 2:
        {
            cout << "------------------------";
            cities.print();
            cout << "------------------------";
            break;
        }
        case 3:
        {
            cities.optimize();
            cout << "�������� ����� ����� �������� ��������������" << endl;
            break;
        }
        default:
            cout << "����� �� ���������...";
            return 0;
        }
    }
}
