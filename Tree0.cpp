#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Tree
{
	long long int Info;
	Tree* Left = NULL, * Right = NULL, * Father = NULL;
};

Tree* Root = NULL;

bool Check_Number(long long int& num)
{
	Tree* node = Root;
	bool status = true;

	while (node != NULL)
	{
		if (node->Info == num) { status = false; break; }
		else if (node->Info < num) node = node->Right;
		else node = node->Left;
	}

	return status;
}

void Add_Number(long long int& num)
{
	Tree* node = Root;
	//Tree* Pr_node;

	if (Root == NULL)
	{
		Root = new Tree;
		Root->Info = num;
		return;
	}

	
	while (true)
	{
		//Pr_node = node;
		if (node->Info < num)
		{
			if (node->Right == NULL)
			{
				node->Right = new Tree;
				node = node->Right;
				break;
			}
			else 
				node = node->Right;
		}
		else
		{
			if (node->Left == NULL)
			{
				node->Left = new Tree;
				node = node->Left;
				break;
			}
			else
				node = node->Left;
		}
	}
	node->Info = num;
}

void Count_Sum(Tree*& Node, long long int& sum)
{//left
	if (Node == NULL) return;
	cout << Node->Info << " ";
	Count_Sum(Node->Left, sum);
	Count_Sum(Node->Right, sum);
	sum += Node->Info;
}

int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	long long int num;
	while (fin.peek() != EOF)
	{
		fin >> num;

		if (Check_Number(num))
			Add_Number(num);
	}

	long long int sum = 0;
	Count_Sum(Root, sum);
	cout << sum;

	fin.close();
	fout.close();

}