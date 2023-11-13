#pragma comment(linker, "/STACK:16777216")
#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;


long long int pro[300005];
long long int tree[1200005];
long long int tree_min[1200005];
long long int tree_max[1200005];

void Push(int v, int tl, int tr)
{
    if (pro[v] == 0) return;

    long long int x = pro[v];
    int temp = tr + tl >> 1;

    tree[2 * v + 1] += x * (temp - tl + 1);
    tree[2 * v + 2] += x * (tr - temp);
    tree_max[2 * v + 1] += x;
    tree_max[2 * v + 2] += x;
    tree_min[2 * v + 1] += x;
    tree_min[2 * v + 2] += x;

    pro[2 * v + 1] += x;
    pro[2 * v + 2] += x;

    pro[v] = 0;
}


long long FindSum(int v, int tl, int tr, int l, int r)
{
    if (l > r)
        return 0;
    if (tl == l && tr == r)
        return tree[v];

    int temp = (tr + tl) >> 1;

    Push(v, tl, tr);
    return  FindSum(v * 2 + 1, tl, temp, l, min(r, temp)) + FindSum(v * 2 + 2, temp + 1, tr, max(l, temp + 1), r);
}

long long FindMin(int v, int tl, int tr, int l, int r)
{
    if (l > r)
        return LLONG_MAX;
    if (tl == l && tr == r)
        return tree_min[v];

    int temp = (tr + tl) >> 1;

    Push(v, tl, tr);
    return  min(FindMin(v * 2 + 1, tl, temp, l, min(r, temp)), FindMin(v * 2 + 2, temp + 1, tr, max(l, temp + 1), r));
}

long long FindMax(int v, int tl, int tr, int l, int r)
{
    if (l > r)
        return LLONG_MIN;
    if (tl == l && tr == r)
        return tree_max[v];

    int temp = (tr + tl) >> 1;

    Push(v, tl, tr);
    return  max(FindMax(v * 2 + 1, tl, temp, l, min(r, temp)), FindMax(v * 2 + 2, temp + 1, tr, max(l, temp + 1), r));
}

void Update(int v, long long int x, int tl, int tr, int l, int r)
{
    if (l > r)
        return;

    if (tl == l && tr == r)
    {
        pro[v] += x;
        tree[v] += x * (tr - tl + 1);
        tree_max[v] += x;
        tree_min[v] += x;
        return;
    }
    Push(v, tl, tr);
    int temp = (tl + tr) >> 1;

    if (l <= temp)
        Update(v * 2 + 1, x, tl, temp, l, min(r, temp));
    if (r > temp)
        Update(v * 2 + 2, x, temp + 1, tr, max(l, temp + 1), r);

    tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
    tree_min[v] = min(tree_min[v * 2 + 1], tree_min[v * 2 + 2]);
    tree_max[v] = max(tree_max[v * 2 + 1], tree_max[v * 2 + 2]);
}

long long int Get(int v, int tl, int tr, int pos)
{
    if (pos == tl && pos == tr)
        return tree[v];

    else
    {
        Push(v, tl, tr);
        int temp = (tl + tr) >> 1;
        if (pos <= temp)
            return Get(v * 2 + 1, tl, temp, pos);
        else
            return Get(v * 2 + 2, temp + 1, tr, pos);
    }
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n, fourn;

    in >> n;
    fourn = 4 * n;


    for (int i = 0; i < fourn; i++)
    {
        tree[i] = 0;
        pro[i] = 0;
        tree_max[i] = 0;
        tree_min[i] = 0;
    }

    int q = -1, a, b, v;
    long long nd;


    while (q)
    {
        in >> q;
        switch (q)
        {
        case 0:
            break;
        case 1:
            in >> a >> v;
            nd = Get(0, 0, n - 1, a);
            Update(0, -nd, 0, n - 1, a, a);
            Update(0, v, 0, n - 1, a, a);
            break;

        case 2:
            in >> a >> b >> v;
            Update(0, v, 0, n - 1, a, b);
            break;
        case 3:
            in >> a >> b;
            out << FindSum(0, 0, n - 1, a, b) << "\n";
            break;
        case 4:
            in >> a >> b;
            out << FindMin(0, 0, n - 1, a, b) << "\n";
            break;
        case 5:
            in >> a >> b;
            out << FindMax(0, 0, n - 1, a, b) << "\n";
            break;
        }
    }

    in.close();
    out.close();

}