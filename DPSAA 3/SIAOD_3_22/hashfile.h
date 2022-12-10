#ifndef HASHFILE_H
#define HASHFILE_H
#include "file.h"
#include "hashtable.h"

bool writeFromBintoTable(Dictionary* table, string path);

bool removeRecord(Dictionary* table, Dictionary dict, const int size, string path);

Dictionary getRecord(Dictionary* table, Dictionary dict, const int size, string path);

#endif