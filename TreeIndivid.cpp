#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Tree
{
    long long int Info, I_Rson, I_Lson, Min_Son, Llen = 0, Rlen = 0, Max = 0; //Max ~ maxlen
    Tree* Right = NULL, * Left = NULL, *Father = NULL;
};
Tree* Root = NULL;

void Add_Node(long long int& num)
{
    Tree* node = Root, * pr_node = NULL, * new_node = new Tree{ num, num, num, num };

    while (node)
    {
        if (node->Info == num)
            return;
        if (node->Info < num)
        {
            if (node->Right == NULL)
            {
                node->Right = new_node;
                new_node->Father = node;
                break;
            }
            node = node->Right;
        }
        else
        {
            if (node->Left == NULL)
            {
                node->Left = new_node;
                new_node->Father = node;
                break;
            }
            node = node->Left;
        }
    }
}

void Calculate_Len(Tree*& node)
{
    if (node == NULL)
        return;

    Calculate_Len(node->Left);
    if (node->Left != NULL)
    {
        node->Llen = node->Left->Max + 1;
        node->I_Lson = node->Left->Min_Son;
    }

    Calculate_Len(node->Right);
    if (node->Right != NULL) // maxlen
    {
        node->Rlen = node->Right->Max + 1;
        node->I_Rson = node->Right->Min_Son;
    }


    if (node->Llen < node->Rlen)
    {
        node->Max = node->Rlen;
        node->Min_Son = node->I_Rson;
    }
    else // if two distances are equal, i should save left son, because he is always less 
    {
        node->Max = node->Llen;
        node->Min_Son = node->I_Lson;
    }
    
}

void Find_Node(Tree*& node, Tree*& delete_node)
{
    if (node == NULL) return;

    long long int len_node = node->Llen + node->Rlen;
    long long int len_delete = (delete_node == NULL) ? 0 : delete_node->Rlen + delete_node->Llen;
    long long int sum_node = node->I_Lson + node->I_Rson;
    long long int sum_del = (delete_node == NULL) ? 0 : delete_node->I_Lson + delete_node->I_Rson;

    if (len_node > len_delete)
        delete_node = node;
    else if (len_node == len_delete && sum_node < sum_del)
        delete_node = node;

    Find_Node(node->Left, delete_node);
    
    Find_Node(node->Right, delete_node);
}

void Delete_less_one_son(Tree*& P)
{
    Tree* R;
    if (P->Left != NULL)
        R = P->Left;
    else R = P->Right;

    if (R != NULL)
        R->Father = P->Father;
    if (P->Father == NULL)
        Root = R;
    //
    else
    {
        if (P->Father->Left == P)
            P->Father->Left = R;
        else
            P->Father->Right = R;
    }
    delete P;
}
void Delete_Node(Tree*& P)
{
    //int node;
    Tree* R;

    if (P->Right == NULL)
        Delete_less_one_son(P);
    else if (P->Right != NULL && P->Left == NULL)
        Delete_less_one_son(P);

    else
    {
        R = P->Right;
        while (R->Left != NULL)
            R = R->Left;
        P->Info = R->Info;
        Delete_less_one_son(R);
    }
}

void Find_Delete_Node(Tree* node, vector <Tree*>& tree)
{
    while (node != NULL)
    {
        if (node->Llen < node->Rlen)
        {
            tree.push_back(node);
            node = node->Right;
        }
        else
        {
            tree.push_back(node);
            node = node->Left;
        }
    }
}

void Print_Node(Tree*& node, ostream& out)
{
    if (node == NULL) return;

    cout << node->Info << endl;
    Print_Node(node->Left, out);

    Print_Node(node->Right, out);
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    long long int num;
    in >> num;
    Root = new Tree{ num, num, num };

    while (in >> num)
    {
        //in >> num;
        Add_Node(num);
    }

    Calculate_Len(Root);
    Tree* Find_N = { 0 };
    
    Find_Node(Root, Find_N);
    //cout << Find_N->Info << " " << Find_N->I_Lson << " " << Find_N->I_Rson << endl;

    long long int k = Find_N->Llen + Find_N->Rlen + 1;
    if (k % 2)
    {
        if (Find_N->Llen != Find_N->Rlen)
        {
            vector <Tree*> tree;
            vector <long long int> info;
            k = (k / 2) + 1;
            //if (Find_N->Llen != Find_N->Rlen)
            
                if ((k - Find_N->Llen) < 0)
                    Find_Delete_Node(Find_N->Left, tree);
                else
                {
                    k -= (Find_N->Llen + 1);
                    Find_Delete_Node(Find_N->Right, tree);
                }
           
            for (int i = 0; i < tree.size(); i++)
                info.push_back(tree[i]->Info);
            sort(info.begin(), info.end());
            for (int i = 0; i < tree.size(); i++)
            {
                if (info[k - 1] == tree[i]->Info)
                {
                    k = i;
                    break;
                }
            }
            Delete_Node(tree[k]);
            //cout << tree[k]->Info << endl;
        }
        else
        {
           // cout << Find_N->Info << endl;
            Delete_Node(Find_N);
        }
    }

    Print_Node(Root, out);

    in.close();
    out.close();
}


//Calculate_Len(node->Left);
//if (node->Left != NULL)
//{
//    node->Llen = node->Left->Llen + 1;
//    node->I_Lson = node->Left->I_Lson;
//}
//
//Calculate_Len(node->Right);
//if (node->Right != NULL)
//{
//    node->Rlen = node->Right->Rlen + 1;
//    node->I_Rson = node->Right->I_Rson;
//    node->Max = (node->Rlen < node->Llen) ? node->Llen : node->Rlen;
//}


//void Print_Node(Tree*& node)
//{
//    if (node == NULL) return;
//    cout << node->Info << " " << node->Llen << " " << node->I_Lson << " " << node->Max << " : " << node->Rlen << " " << node->I_Rson << endl;
//    Print_Node(node->Left);
//
//    Print_Node(node->Right);
//}