#ifndef HASHYABLE_H
#define HASHYABLE_H

#include <string.h>
#include "Dictionary.h"

int hashFunc(Dictionary dict);

bool insertRecordToTable(Dictionary* dictionaries, Dictionary dict,  const int size);

bool removeRecordFromTable(Dictionary* dictionaries, Dictionary dict, const int size);

int getRecordIndex(Dictionary* dictionaries, Dictionary dict, const int size);

bool rehashTable(Dictionary*& dictionaries, int& size);

#endif