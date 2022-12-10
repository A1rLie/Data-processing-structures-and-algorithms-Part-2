#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
	head = new Node();
}

bool BinaryTree::createTree(string path)
{
	ifstream fin;
	fin.open(path, ios::binary | ios::in);
	Dictionary dict;

    if (fin.is_open())
    {
        int index = 0;
        while (fin.read((char*)&dict, sizeof(Dictionary)))
        {
            addNode(dict, index);
            index++;
        }
        fin.close();
        return true;
    }
    return false;
}

void BinaryTree::addNode(Dictionary dict, int index)
{
    Node* temp = head;
    while (true)
    {
        if (strcmp(temp->value.englishWord, "") == 0)
        {
            temp->value = dict;
            temp->index = index;
            break;
        }
        else if (temp->value.englishWord[0] - dict.englishWord[0] < 0)
        {
            if (temp->right == nullptr) temp->right = new Node;
            temp = temp->right;
        }
        else
        {
            if (temp->left == nullptr) temp->left = new Node;
            temp = temp->left;
        }
    }
}

int BinaryTree::findNode(char key[10])
{
    Node* temp = head;
    while (true)
    {
        if (temp == nullptr) return -1;
        else if (strcmp(temp->value.englishWord, key) == 0)
        {
            return temp->index;
        }
        else if (temp->value.englishWord[0] - key[0] < 0)
        {
            temp = temp->right;
        }
        else
        {
            temp = temp->left;
        }
    }
    return -1;
}

BinaryTree::Node* BinaryTree::findMinNode(Node* node, Node* parent, int left)
{
    if (node->left == nullptr)
    {
        parent->left = nullptr;
        return node;
    }
    return findMinNode(node->left, node, true);
}


bool BinaryTree::removeNode(char key[10])
{
    Node* temp = head;
    Node* parent = head;
    int flag = 0;
    if (findNode(key) == -1) return false;
    while (true)
    {
        if (strcmp(temp->value.englishWord, key) == 0)
        {
            if (flag) parent->right = nullptr;
            else parent->left = nullptr;

            if (temp->left == nullptr && temp->right == nullptr)
            {
                delete temp;
            }
            else if (temp->left == nullptr)
            {
                parent->right = temp->right;
                delete temp;
            }
            else if (temp->right == nullptr)
            {
                parent->left = temp->left;
                delete temp;
            }
            else
            {
                Node* res = findMinNode(temp->right, temp, true);
                res->left = temp->left;
                res->right = temp->right;
                delete temp;
                if (flag) parent->right = res;
                else parent->left = res;
            }
            return true;
        }
        else if (temp->value.englishWord[0] - key[0] < 0)
        {
            flag = 1;
            parent = temp;
            temp = temp->right;
        }
        else
        {
            flag = 0;
            parent = temp;
            temp = temp->left;
        }
    }
    return false;
}

void BinaryTree::print(Node* node, string space)
{
    if (node->right != nullptr) print(node->right, space + "    ");
    cout << space << node->value.englishWord << " " << node->value.russianWord << endl;
    if (node->left != nullptr) print(node->left, space + "    ");
}

void BinaryTree::printTree()
{
    print(head, "center");
}