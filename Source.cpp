#include <iostream>

using namespace std;

struct Node
{
	int i;
	Node* pLeft;
	Node* pRight;

	Node(int iIn) : i(iIn), pLeft(nullptr), pRight(nullptr) {}
};

void InsertToTree(Node*& pRoot, Node* pNew)
{
	if (!pRoot)
	{
		pRoot = pNew;
		return;
	}

	if (pNew->i <= pRoot->i)
		InsertToTree(pRoot->pLeft, pNew);
	else
		InsertToTree(pRoot->pRight, pNew);
}

void DeleteNodeWithTwoChildren(Node*& q, Node*& p)
{
	if (p->pRight)
	{
		DeleteNodeWithTwoChildren(q, p->pRight);
		return;
	}

	p->i = q->i;
	q = p;
	p = p->pLeft;
}

void DeleteNodeFromTree(Node*& pRoot, int i)
{
	if (!pRoot)
		return;

	if (pRoot->i < i)
	{
		DeleteNodeFromTree(pRoot->pRight, i);
		return;
	}

	if (pRoot->i > i)
	{
		DeleteNodeFromTree(pRoot->pLeft, i);
		return;
	}

	Node* q = pRoot;
	if (!q->pRight)
		pRoot = q->pLeft;
	else if (!q->pLeft)
		pRoot = q->pRight;
	else
		DeleteNodeWithTwoChildren(q, q->pLeft);

	delete q;
}

void PrintTree(Node* pRoot, int Level)
{
	if (!pRoot)
		return;

	PrintTree(pRoot->pRight, Level + 1);

	for (int i = 0; i < Level; i++)
		cout << "  ";
	cout << pRoot->i << endl;

	PrintTree(pRoot->pLeft, Level + 1);
}

void Insert(Node*& pRoot, Node* pNewNode)
{
	if (!pRoot)
		pRoot = pNewNode;
	else
	{
		if (pNewNode->i < pRoot->i)
			Insert(pRoot->pLeft, pNewNode);
		else
			Insert(pRoot->pRight, pNewNode);
	}
}

double searching_max_sum(Node* Rootp)
{
	if (Rootp == nullptr)
		return 0;
	double left = searching_max_sum(Rootp->pLeft);
	double right = searching_max_sum(Rootp->pRight);
	
	if(left > right){
		return (left + Rootp->i);
	}
	else {
		return(right + Rootp->i);
	}
}

bool print_the_road(Node* Rootp, int sum)
{
	if (sum == 0)
		return true;

	if (Rootp == nullptr)
		return false;
	bool leftSide = print_the_road(Rootp->pLeft, sum - Rootp->i);
	bool rightSide = print_the_road(Rootp->pRight, sum - Rootp->i);

	if (leftSide || rightSide) {
		cout << Rootp->i << " ";
	}
	return leftSide || rightSide;
	
}

void writingToConsole(Node* Rootp)
{
	int sum = searching_max_sum(Rootp);
	cout << "The maximum sum of the tree is " << sum << endl;
	cout << "The way that gives that sum is "; 
	cout << print_the_road(Rootp, sum);
}

void main()
{
	int i;

	Node* pRoot = nullptr;
	while (true)
	{
		cin >> i;
		if (i == 99)
			break;

		Node* p = new Node(i);
		InsertToTree(pRoot, p);
	}

	PrintTree(pRoot, 1);

	writingToConsole(pRoot);
}