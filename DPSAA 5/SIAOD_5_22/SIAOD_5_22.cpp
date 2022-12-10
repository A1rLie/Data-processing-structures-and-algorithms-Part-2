//#include <iostream>
//#include "binaryFile.h"
//#include "BinaryTree.h"
//
//using namespace std;
//
//int main()
//{
//    system("chcp 1251 > null");
//    
//    string bin;
//    string txt;
//    cout << "Введите путь до текстового файла >> ";
//    cin >> txt;
//
//    cout << "Введите путь до бинарного файла >> ";
//    cin >> bin;
//
//    convertTextToBin(txt, bin);
//
//    BinaryTree tree;
//    tree.createTree(bin);
//    while (true)
//    {
//        int choice;
//        cout << "1. Добавление словаря\n2. Поиск словаря по ключу\n3. Удаление словаря по ключу\n4. Вывод дерева\n>> ";
//        cin >> choice;
//        switch (choice)
//        {
//        case 1:
//        {
//            Dictionary dict;
//            cout << "Английское слово >> ";
//            cin.clear();
//            cin.ignore();
//            gets_s(dict.englishWord);
//            cout << "Русское слово >> ";
//            gets_s(dict.russianWord);
//            int index = 0;
//            addDictionary(bin, dict, index);
//            tree.addNode(dict, index);
//            break; 
//        }
//        case 2:
//        {
//            char buf[10];
//            cout << "Ключ  >> ";
//            cin.clear();
//            cin.ignore();
//            gets_s(buf);
//            int index = tree.findNode(buf);
//            cout << "Индекс: " << index << endl;
//            getAndPrintDictionary(bin, index);
//            break;
//        }
//        case 3:
//        {
//            char buf[10];
//            cin.clear();
//            cin.ignore();
//            cout << "Ключ  >> ";
//            gets_s(buf);
//            tree.removeNode(buf);
//            break;
//        }
//        case 4:
//        {
//            cout << "----------------------------" << endl;
//            tree.printTree();
//            cout << "----------------------------" << endl;
//            break;
//        }
//        default:
//            cout << "Завершение программы..." << endl;
//            return 0;
//            break;
//        }
//    }
//}
