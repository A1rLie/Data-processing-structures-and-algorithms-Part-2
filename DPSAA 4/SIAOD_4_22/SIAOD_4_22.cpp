#include <iostream>
#include <stack>
#include <queue>
#include <string>

using namespace std;

class Tree 
{
private:
	struct Node
	{
		char value = 0;
		Node* left;
		Node* right;

		Node()
		{
			left = nullptr;
			right = nullptr;
		}
	};

	Node* head;
	string result;

	Node* findTopForOps(Node* node)
	{
		if (node->value == 0) return node;
		if (node->left == nullptr) return node->left = new Node();
		if (node->right == nullptr) return node->right = new Node();
		if (node->left != nullptr && (node->left->value < '0' || node->left->value > '9')) findTopForOps(node->left);
		if (node->right != nullptr && (node->right->value < '0' || node->right->value > '9')) findTopForOps(node->right);
		else return node;
	}

	void printTree(Node* temp, string space)
	{
		if (temp->right != nullptr) printTree(temp->right, space + "    ");
		cout << space + temp->value << endl;
		if (temp->left != nullptr) printTree(temp->left, space + "    ");
	}

	 
	Node* remake(Node* node)
	{
		if (node->left != nullptr && (node->left->value < '0' || node->left->value > '9')) node->left = remake(node->left);
		if (node->right != nullptr && (node->right->value < '0' || node->right->value > '9')) node->right = remake(node->right);

		Node* res = node;
		if (node->value == '-' || node->value == '+' || node->value == '*')
		{
			if (node->left->value == '0' && node->value != '*')
			{
				delete node->left;
				node->left = nullptr;
				res = node->right;
			}
			else if (node->right->value == '0' && node->value != '*')
			{
				delete node->right;
				node->right = nullptr;
				res = node->left;
			}
			else if (node->left->value == '0' && node->value == '*')
			{
				delete node->right;
				node->right = nullptr;
				res = node->left;
			}
			else if (node->right->value == '0' && node->value == '*')
			{
				delete node->left;
				node->left = nullptr;
				res = node->right;
			}
			else if (node->right->value == '1' && node->value == '*')
			{
				delete node->right;
				node->right = nullptr;
				res = node->left;
			}
			else if (node->left->value == '1' && node->value == '*')
			{
				delete node->left;
				node->left = nullptr;
				res = node->right;
			}
		}
		return res;
	}

public:
	Tree()
	{
		head = new Node();
	}

	void createTree(string expression)
	{
		Node* tempTop = head;
		tempTop->value = expression[0];
		for (int i = 1; i < expression.length(); i++)
		{
			switch (expression[i])
			{
			case '+':
			case '-':
			case '*':
			case '/':
				tempTop = findTopForOps(head);
				tempTop->value = expression[i];
				continue;
			default:
			{
				if (tempTop->left == nullptr)
				{
					tempTop->left = new Node();
					tempTop->left->value = expression[i];
				}
				else
				{
					tempTop->right = new Node();
					tempTop->right->value = expression[i];
				}
			}
				break;
			}
		}
	}

	void print()
	{
		printTree(head, "");
	}

	void printWidthTree()
	{
		queue<Node*> queue;
		queue.push(head);
		while (!queue.empty())
		{
			Node* temp = queue.front();
			cout << temp->value;
			if (temp->left != nullptr) queue.push(temp->left);
			if (temp->right != nullptr) queue.push(temp->right);
			queue.pop();
		}
	}

	void remakeTree()
	{
		head = remake(head);
	}
};

string convertToPrefix(string expression)
{
	if (expression.length() == 1) return expression;
	stack<char> operationsStack;

	stack<string> expressionStack;

	for (int i = 0; i < expression.length(); i++)
	{
		if (expression[i] == '(') continue;
		else if (expression[i] == ')')
		{
			char op = operationsStack.top();
			operationsStack.pop();

			string operand1 = expressionStack.top();
			expressionStack.pop();

			string operand2 = expressionStack.top();
			expressionStack.pop();
			string temp = op + operand2 + operand1;
			expressionStack.push(temp);
		}
		else
		{
			switch (expression[i])
			{
			case '+':
			case '-':
			case '/':
			case '*':
				operationsStack.push(expression[i]);
				break;
			default:
				expressionStack.push(to_string(expression[i] - 48));
				break;
			}
		}
	}
	
	return expressionStack.top();
}

int main()
{
	system("chcp 1251 > null");
	Tree tree;
	cout << "Введите выражение с соблюдением всех скобок! >> ";
	string expression;
	cin >> expression;
	tree.createTree(convertToPrefix(expression));

	while (true)
	{
		int choice;
		cout << "1. Отображение дерева, повернутого против часовой стрелки\n" <<
			"2. Отображение дерева в ширину\n" <<
			"3. Упрощение дерева\n" <<
			">>> ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			tree.print();
			break;
		case 2:
			tree.printWidthTree();
			break;
		case 3:
			tree.remakeTree();
			break;
		default:
			cout << "Завершение программы...";
			return 1;
			break;
		}
	}
}
