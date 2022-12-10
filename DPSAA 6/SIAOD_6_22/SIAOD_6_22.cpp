#include "Grapgh.h"

int main()
{
    system("chcp 1251 > null");
    Grapth gr;
    int choice;
    while (true)
    {
        cout << "1. Добавление элемента в граф\n2. Вывод графа\n3. Нахождение кратчейшего пути\n4. Нахождение эксцентриситета вершины\n>> ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            int first, second, destination;
            cout << "Введите номер первой вершины, второй и расстояние между ними >> ";
            cin >> first >> second >> destination;
            if (gr.add(first, second, destination) == false) cout << "Вершины нужно вводить линейно!";
            break;
        }
        case 2:
        {
            cout << "------------------------";
            gr.print();
            cout << "------------------------";
            break;
        }
        case 3:
        {
            int start, finish;
            cout << "Номер начальной и конечной вершины >> ";
            cin >> start >> finish;
            int res = gr.getBellmanFord(start, finish);
            if (res == -1) cout << "Одна из вершин превосходит размер графа!";
            else cout << res << endl;
            break;
        }
        case 4:
        {
            int top;
            cout << "Номер вершины >> ";
            cin >> top;
            int res = gr.findEccentricity(top);
            if (res == -1) cout << "Вершина превосходит размер графа или граф пуст!";
            else cout << res << endl;
            break;
        }
        default:
            cout << "Выход из программы...";
            return 0;
        }
    }
}
