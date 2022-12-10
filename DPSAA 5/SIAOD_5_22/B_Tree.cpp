#include "B_Tree.h"

void B_Tree::sort(Node* node)
{
	for (int i = 0; i < node->valuesLength; i++)
	{
		for (int j = i+1; j < node->valuesLength; j++)
		{
			if (node->values[i].dict.englishWord[0] > node->values[j].dict.englishWord[0]) swap(node->values[i], node->values[j]);
		}
	}
}

B_Tree::B_Tree()
{
	head = nullptr;
}

B_Tree::Node* B_Tree::findPlaceForNode(Node* node, char key[10])
{
	if (node->child0 != nullptr)
	{
		if (key[0] < node->values[0].dict.englishWord[0])
		{
			findPlaceForNode(node->child0, key);
		}
		else if (node->valuesLength == 2 && key[0] >= node->values[1].dict.englishWord[0])
		{
			findPlaceForNode(node->child2, key);
		}
		else
		{
			findPlaceForNode(node->child1, key);
		}
	}
	else return node;
}

B_Tree::DictWithIndex B_Tree::rebuildTree(Node* node, const Dictionary nodeKey, DictWithIndex value)
{
	if (strcmp(node->values[0].dict.englishWord, nodeKey.englishWord) == 0) //”зел, который нужен
	{
		//ѕодстраиваем позицию value в массиве, то что по центру - уходит наверх
		if (value.dict.englishWord[0] < node->values[0].dict.englishWord[0])
		{
			swap(node->values[0], node->values[1]);
			swap(node->values[0], value);
		}
		else if (value.dict.englishWord[0] > node->values[0].dict.englishWord[0] && value.dict.englishWord[0] <= node->values[1].dict.englishWord[0])
		{
			swap(value, node->values[1]);
		}

		DictWithIndex result = node->values[1];
		node->values[1] = value;
		return result;
	}
	else if (nodeKey.englishWord[0] < node->values[0].dict.englishWord[0])
	{
		DictWithIndex result = rebuildTree(node->child0, nodeKey, value);
		if (result.index != -1)
		{
			if (node->valuesLength < 2)
			{
				node->values[node->valuesLength] = result;
				node->valuesLength++;
				sort(node);
				Node* left = new Node;
				left->values[0] = node->child0->values[0];
				left->valuesLength++;
				left->child0 = node->child0->child0;
				left->child1 = node->child0->child1;

				Node* right = new Node;
				right->values[0] = node->child0->values[1];
				right->valuesLength++;
				right->child0 = node->child0->child2;
				right->child1 = node->child0->child3;

				node->child0 = left;
				node->child2 = node->child1;
				node->child1 = right;
				DictWithIndex empty;
				return empty;
			}
			else
			{
				if (result.dict.englishWord[0] < node->values[0].dict.englishWord[0])
				{
					swap(result, node->values[0]);
				}
				else if (result.dict.englishWord[0] > node->values[1].dict.englishWord[0])
				{
					swap(result, node->values[1]);
				}
				Node* lessNode = new Node;
				lessNode->values[0] = node->child0->values[0];
				lessNode->valuesLength++;
				lessNode->child0 = node->child0->child0;
				lessNode->child1 = node->child0->child1;

				Node* greaterNode = new Node;
				greaterNode->values[0] = node->child0->values[1];
				greaterNode->valuesLength++;
				greaterNode->child0 = node->child0->child2;
				greaterNode->child1 = node->child0->child3;

				delete node->child0;
				node->child0 = lessNode;
				node->child3 = node->child2;
				node->child2 = node->child1;
				node->child1 = greaterNode;
				return result;
			}
		}
		else return result;
	}
	else if (node->valuesLength == 2 && nodeKey.englishWord[0] >= node->values[1].dict.englishWord[0])
	{
		DictWithIndex result = rebuildTree(node->child2, nodeKey, value);
		if (result.index != -1)
		{
			if (node->valuesLength < 2)
			{
				node->values[node->valuesLength] = result;
				node->valuesLength++;
				Node* left = new Node;
				left->values[0] = node->values[0];
				left->valuesLength++;
				left->child0 = node->child0;
				left->child1 = node->child1;

				Node* right = new Node;
				right->values[0] = node->values[1];
				right->valuesLength++;
				right->child0 = node->child2;
				right->child1 = node->child3;
				DictWithIndex empty;
				return empty;
			}
			else
			{
				if (result.dict.englishWord[0] < node->values[0].dict.englishWord[0])
				{
					swap(result, node->values[0]);
				}
				else if (result.dict.englishWord[0] > node->values[1].dict.englishWord[0])
				{
					swap(result, node->values[1]);
				}
				Node* lessNode = new Node;
				lessNode->values[0] = node->child2->values[0];
				lessNode->valuesLength++;
				lessNode->child0 = node->child2->child0;
				lessNode->child1 = node->child2->child1;

				Node* greaterNode = new Node;
				greaterNode->values[0] = node->child2->values[1];
				greaterNode->valuesLength++;
				greaterNode->child0 = node->child2->child2;
				greaterNode->child1 = node->child2->child3;

				delete node->child2;
				node->child2 = lessNode;
				node->child3 = greaterNode;
				return result;
			}
		}
		else return result;
	}
	else
	{
		DictWithIndex result = rebuildTree(node->child1, nodeKey, value);
		if (result.index != -1)
		{
			if (node->valuesLength < 2)
			{
				node->values[node->valuesLength] = result;
				node->valuesLength++;
				sort(node);
				Node* left = new Node;
				left->values[0] = node->child1->values[0];
				left->valuesLength++;
				left->child0 = node->child1->child0;
				left->child1 = node->child1->child1;

				Node* right = new Node;
				right->values[0] = node->child1->values[1];
				right->valuesLength++;
				right->child0 = node->child1->child2;
				right->child1 = node->child1->child3;

				node->child1 = left;
				node->child2 = right;
				DictWithIndex empty;
				return empty;
			}
			else
			{
				if (result.dict.englishWord[0] < node->values[0].dict.englishWord[0])
				{
					swap(result, node->values[0]);
				}
				else if (result.dict.englishWord[0] > node->values[1].dict.englishWord[0])
				{
					swap(result, node->values[1]);
				}
				Node* lessNode = new Node;
				lessNode->values[0] = node->child1->values[0];
				lessNode->valuesLength++;
				lessNode->child0 = node->child1->child0;
				lessNode->child1 = node->child1->child1;

				Node* greaterNode = new Node;
				greaterNode->values[0] = node->child1->values[1];
				greaterNode->valuesLength++;
				greaterNode->child0 = node->child1->child2;
				greaterNode->child1 = node->child1->child3;

				delete node->child1;
				node->child1 = lessNode;
				node->child3 = node->child2;
				node->child2 = greaterNode;
				return result;
			}
		}
		else return result;
	}
}

void B_Tree::addNode(Dictionary Dict, int index)
{
	if (head == nullptr)
	{
		head = new Node;
		head->values[0].dict = Dict;
		head->values[0].index = index;
		head->valuesLength++;
		return;
	}
	else
	{
		Node* node = findPlaceForNode(head, Dict.englishWord);
		if (node->valuesLength < 2)
		{
			node->values[node->valuesLength].dict = Dict;
			node->values[node->valuesLength].index = index;
			node->valuesLength++;
			sort(node);
		}
		else
		{
			DictWithIndex value;
			value.dict = Dict;
			value.index = index;
			DictWithIndex temp = rebuildTree(head, node->values[0].dict, value);
			if (temp.index != -1)
			{
				if (temp.dict.englishWord[0] < head->values[0].dict.englishWord[0])
				{
					swap(head->values[0], temp);
				}
				else if (temp.dict.englishWord[0] > head->values[1].dict.englishWord[0])
				{
					swap(temp, head->values[1]);
				}

				Node* tempNode = head;
				head = new Node;
				
				head->values[0] = temp;
				head->valuesLength++;

				Node* left = new Node;
				left->values[0] = tempNode->values[0];
				left->valuesLength++;
				left->child0 = tempNode->child0;
				left->child1 = tempNode->child1;

				Node* right = new Node;
				right->values[0] = tempNode->values[1];
				right->valuesLength++;
				right->child0 = tempNode->child2;
				right->child1 = tempNode->child3;

				head->child0 = left;
				head->child1 = right;
			}
		}
	}
}