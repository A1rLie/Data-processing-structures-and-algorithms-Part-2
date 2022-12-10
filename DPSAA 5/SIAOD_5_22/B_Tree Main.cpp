#include <iostream>
#include "B_Tree.h"

using namespace std;

int main()


{
    system("chcp 1251 > null");

    string bin;
    string txt;
    //cout << "¬ведите путь до текстового файла >> ";
    txt = "C:\\Users\\defox\\Desktop\\text.txt";

    //cout << "¬ведите путь до бинарного файла >> ";
    bin = "bin.bin";

    //convertTextToBin(txt, bin);

    B_Tree tree;
    Dictionary dict;
    strcpy_s(dict.englishWord, "apple");
    tree.addNode(dict, 1);
    strcpy_s(dict.englishWord, "joker");
    tree.addNode(dict, 1);
    strcpy_s(dict.englishWord, "gear");
    tree.addNode(dict, 1);
    strcpy_s(dict.englishWord, "banana");
    tree.addNode(dict, 1);
    strcpy_s(dict.englishWord, "carrot");
    tree.addNode(dict, 1);
    strcpy_s(dict.englishWord, "aist");
    tree.addNode(dict, 1);
    strcpy_s(dict.englishWord, "app");
    tree.addNode(dict, 1);
    strcpy_s(dict.englishWord, "vi");
    tree.addNode(dict, 1);
    strcpy_s(dict.englishWord, "fedor");
    tree.addNode(dict, 1);
    strcpy_s(dict.englishWord, "zetta");
    tree.addNode(dict, 1);
    strcpy_s(dict.englishWord, "zebra");
    tree.addNode(dict, 1);
    strcpy_s(dict.englishWord, "zayac");
    tree.addNode(dict, 1);
}