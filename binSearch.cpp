#include <iostream>
#include <vector>
using namespace std;

int moreSearch(long long& temp, long long*& a, int& n, int l, int r)
{
    int m;
    while (l + 1 < r)
    {
        m = (l + r) / 2;
        if (a[m] < temp)
            l = m;
        else if (a[m] > temp)
            r = m;
        else
            l = m;
    }

    if (a[l] > temp)
        return l;
    if (a[r] > temp)
        return r;
    else
        return n;
}

int eq_moreSearch(long long& temp, long long*& a, int& n, int l, int r)
{
    int m;
    while (l + 1 < r)
    {
        m = (l + r) / 2;
        if (a[m] < temp)
            l = m;
        else if (a[m] > temp)
            r = m;
        else
            r = m;
    }

    if (a[l] >= temp)
        return l;
    if (a[r] >= temp)
        return r;
    else
        return n;
}

int binSearch(long long& temp, long long*& a, int& n, int l, int r)
{
    int m;
    while (l+1 < r)
    {
        m = (l + r) / 2;
        if (a[m] < temp)
            l = m;
        else if (a[m] > temp)
            r = m;
        else
            r = m;
    }

    if (a[l] == temp)
        return l;
    if (a[r] == temp)
        return r;
    else
        return n;
}

int main()
{
    int n, k, i, index;
    long long int temp;

    cin >> n;
    long long int* a = new long long int[n];
    for (i = 0; i < n; i++)
        cin >> a[i];

    cin >> k;
    long long int* task = new long long int[k];
    for (i = 0; i < k; i++)
        cin >> task[i];

    for (i = 0; i < k; i++)
    {
        temp = task[i];
        // ==
        index = binSearch(temp, a, n, 0, n - 1);
        if (index == n)
        {
            index = 0;
            cout << "0 ";
        }
        else
            cout << "1 ";
        // >=
        index = (task[i] <= a[index]) ? index : eq_moreSearch(temp, a, n, index, n - 1);
        cout << index << " ";
        // >
        index = (task[i] < a[index]) ? index : moreSearch(temp, a, n, index, n - 1);
        cout << index << endl;

    }
}
