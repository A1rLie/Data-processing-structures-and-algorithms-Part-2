#include "hashfile.h"

bool writeFromBintoTable(Dictionary* table, string path)
{
    Dictionary dict;
	int i = 0;

	while (strcmp((dict = getRecordFromBin(path,i)).englishWord,"") != 0)
	{
		table[i] = dict;
		table[i].noteNumber = i;
		i++;
	}
	return true;
}

bool removeRecord(Dictionary* table, Dictionary dict, const int size, string path)
{
	int index = getRecordIndex(table, dict, size);
	if (index != -1)
	{
		removeRecordFromTable(table, dict, size);
		removeRecordFromBin(path, index);
		return true;
	}
	return false;
}

Dictionary getRecord(Dictionary* table, Dictionary dict, const int size, string path)
{
	Dictionary dictFromFile;
	int index = getRecordIndex(table, dict, size);
	if (index != -1)
	{
		dictFromFile = getRecordFromBin(path, index);
	}
	return dictFromFile;
}
