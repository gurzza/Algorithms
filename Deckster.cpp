#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;



int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n, m, v, u, cost;

    in >> n >> m;
    bool* status = new bool[n];
    vector <long long int> dis(n, LLONG_MAX);

    vector <vector <pair <int, int> > > a(n);
    for (int i = 0; i < m; i++)
    {
        in >> v >> u >> cost;
        a[v - 1].push_back(make_pair(u - 1, cost));
        a[u - 1].push_back(make_pair(v - 1, cost));
    }
    in.close();


    dis[0] = 0;
    for (int i = 0; i < n; i++)
        status[i] = 0;


    priority_queue <pair <long long int, int > > q;
    int temp;
    long long int d;

    q.push(make_pair(0, 0));
    while(!q.empty())
    {
        /*temp = -1;
        for (int i = 0; i < n; i++)
        {
            if (!status[i] && (temp == -1 || dis[i] < dis[temp]))
                temp = i;
        }*/
        temp = q.top().second;
        d = -q.top().first;
        q.pop();

        if (d > dis[temp])
            continue;

        status[temp] = true;
        for (int i = 0; i < a[temp].size(); i++)
        {
            v = a[temp][i].first;
            cost = a[temp][i].second;

            if (cost + dis[temp] < dis[v])
            {
                dis[v] = cost + dis[temp];
                q.push(make_pair(-dis[v], v));
            }
        }
    }

    cout << dis[n - 1];
    out.close();
}