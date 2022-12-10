#ifndef B_TREE_H
#define B_TREE_H
#include "binaryFile.h"

class B_Tree
{
public:

	struct DictWithIndex
	{
		Dictionary dict;
		int index = -1;
	};

	struct Node
	{
		bool isLeaf = true;
		DictWithIndex values[2];
		int valuesLength = 0;
		Node* child0 = nullptr;
		Node* child1 = nullptr;
		Node* child2 = nullptr;
		Node* child3 = nullptr; //Для обработки п
	};

	Node* head;

	void sort(Node* node);

	void append(Node* node, Dictionary dictionary, int index);

	DictWithIndex rebuildTree(Node* node, const Dictionary nodeKey, DictWithIndex value);

	Node* findPlaceForNode(Node* node, char key[10]);

public:
	B_Tree();

	

	void addNode(Dictionary Dict, int index);



};
#endif 

