#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;


int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    string s;

    in >> s;
    int sz = s.size();
    int** m = new int*[sz];
    for (int i = 0; i < sz; i++)
    {
        m[i] = new int[sz];
        m[i][i] = 1;
    }
    for (int i = 0; i < sz - 1; i++)
        m[i + 1][i] = 0;

    for (int j = 0; j < sz; j++)
    {
        for (int i = j-1; i > -1; i--)
        {
            if (s[i] == s[j])
                m[i][j] = m[i + 1][j - 1] + 2;
            else
                m[i][j] = max(m[i + 1][j], m[i][j - 1]);
        }
    }

    int k = sz - 1;// , z = 0;
    string res = "";
    int i = 0;
    while (i <= k)
    {
        if (s[k] == s[i])
        {
            res += s[k];
            k--;
            i++;
        }

        else
            m[i][k] == m[i+1][k] ? i = i + 1 : k = k - 1;
    }
    
    k = m[0][sz - 1];
    for (i = (k / 2) - 1; i > -1; i--)
    {
        res += res[i];
    }
    out << k << endl << res;

    in.close();
    out.close();
}