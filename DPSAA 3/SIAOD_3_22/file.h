#ifndef FILE_H
#define FILE_H
#include "Dictionary.h"
#include <fstream>

using namespace std;

bool convertTextToBin(string pathToRead, string pathToWrite);

bool isLess(string path, int index);

bool removeRecordFromBin(string path, int index);

Dictionary getRecordFromBin(string path, int index);

bool addRecordToBin(string path, Dictionary dict);

#endif