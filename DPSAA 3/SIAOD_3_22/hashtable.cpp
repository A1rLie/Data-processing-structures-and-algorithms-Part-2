#include "hashtable.h"

int hashFunc(Dictionary dict)
{
	return dict.englishWord[0] - 97;
}

bool insertRecordToTable(Dictionary* dictionaries, Dictionary dict, const int size)
{
	int index = hashFunc(dict);
	while (index < size)
	{
		if (strcmp(dictionaries[index].englishWord, "") == 0)
		{
			dictionaries[index] = dict;
			return true;
		}
		index++;
	}

	return false;
}

bool removeRecordFromTable(Dictionary* dictionaries, Dictionary dict, const int size)
{
	int index = hashFunc(dict);
	while (index < size)
	{
		if (strcmp(dictionaries[index].englishWord, dict.englishWord) == 0)
		{
			strcpy_s(dictionaries[index].englishWord, "");
			strcpy_s(dictionaries[index].russianWord, "");
			dictionaries[index].noteNumber = -1;
			return true;
		}
		index++;
	}

	return false;
}

int getRecordIndex(Dictionary* dictionaries, Dictionary dict,  const int size)
{
	int index = hashFunc(dict);
	while (index < size)
	{
		if (strcmp(dictionaries[index].englishWord, "") == 0) break;

		if (strcmp(dictionaries[index].englishWord, dict.englishWord) == 0) return dictionaries[index].noteNumber;

		index++;
	}

	return -1;
}

bool rehashTable(Dictionary*& dictionaries, int& size)
{
	Dictionary* newDict = new Dictionary[size * 1.5];
	for (int i = 0; i < size; i++)
	{
		newDict[i] = dictionaries[i];
	}

	delete[] dictionaries;

	dictionaries = newDict;
	size *= 1.5;

	return true;
}
