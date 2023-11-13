#include <iostream>
#include <vector>
#include <fstream>
#include <list>
using namespace std;

int FindSet(int*& node, int& v)
{
    if (node[v] == v)
        return v;

    return node[v] = FindSet(node, node[v]);
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n, q, u, v, comp, min_sz, father, father_v, father_u, m;
    vector <pair <int, int>> v_p;
    vector <list <int>> v_l;

    cin >> n >> m >> q;
    int* node = new int[n];
    int* sz = new int[n];

    for (int i = 0; i < n; i++)
    {
        node[i] = i;
        sz[i] = 0;
        //v_l.push_back(list <int>(0));
    }

    for (int i = 0; i < m; i++)
    {
        cin >> u >> v;
        --u; --v;
        //v_p.push_back(make_pair(u, v));
        //v_l[u].push_back(v);
        //v_l[v].push_back(u);

        father_u = FindSet(node, u);
        father_v = FindSet(node, v);
        if (father_u == father_v)
        {
            sz[u]++;
            sz[v]++;
        }

        else
        {
            min_sz = (sz[father_u] <= sz[father_v]) ? father_u : father_v;
            father = father_u + father_v - min_sz;
            
            //father = FindSet(node, father);

            node[min_sz] = father;
            //sz[father]++;
            sz[u]++;
            sz[v]++;
            //sz[min_sz]++;
        }

    }

    //sz-?


    for (int i = 0; i < n; i++)
        cout << sz[i] << " ";


    in.close();
    out.close();
}