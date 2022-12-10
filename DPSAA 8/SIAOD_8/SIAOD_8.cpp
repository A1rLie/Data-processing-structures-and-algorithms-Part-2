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
        cout << "1. Добавление города\n2. Вывод графа связи городов\n3. Оптимизация дорог\n>> ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            int first, second, weight;
            cout << "Введите номер первого города, второго и загруженность дороги между ними >> ";
            cin >> first >> second >> weight;
            if (cities.add(first, second, weight) == false) cout << "Вершины нужно вводить с возрастанием!";
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
            cout << "Строение дорог между городами оптимизировано" << endl;
            break;
        }
        default:
            cout << "Выход из программы...";
            return 0;
        }
    }
}
