#ifndef BINARY_TREE
#define BINARY_TREE
#include "binaryFile.h"

class BinaryTree
{
private:

	struct Node
	{
		Dictionary value;
		int index = -1;
		Node* left = nullptr;
		Node* right = nullptr;
	};

	Node* head;

	void print(Node* node, string space = "");

	Node* findMinNode(Node* node, Node* parent, int left);

public:
	BinaryTree();

	bool createTree(string path);

	void addNode(Dictionary dict, int index);

	int findNode(char key[10]);

	bool removeNode(char key[10]);

	void printTree();
};

#endif 
