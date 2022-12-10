#ifndef BINARYFILE_H
#define BINARYFILE_H
#include "Dictionary.h"
#include <fstream>
#include <iostream>

using namespace std;

bool convertTextToBin(string pathToRead, string pathToWrite);

bool isLess(string path, int index);

bool searchAndPrintDictionary(string path, char key[10]);

bool getAndPrintDictionary(string path, int index);

bool addDictionary(string path, Dictionary dict, int& index);

#endif