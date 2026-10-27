#include <bits/stdc++.h>
using namespace std;
int query(int u, int v)
{
    cout << "? " << u << " " << v << endl;
    int r;
    cin >> r;
    return r;
}
void solved()
{
    int n;
    cin >> n;
    vector<int> fa(n, 0);
    list<int> que; 
    fa[1] = 0;
    que.push_back(1);
    int k = -1;
    for (int i = 2; i < n; i++)
    {
        if (query(1, i) == 1)
        {
            fa[i] = 0;
            que.push_back(i);
        }
        else
        {
            fa[i] = 1;
            k = i;
            break;
        }
    }
    que.front() = k;
    auto it = que.begin();
    if (que.size() > 1)
    {
        it++;
    }
    for (int i = k + 1; i < n; i++)
    {
        while (query(*it, i) == 1)
        {
            it = que.erase(it);
            if (it == que.end())
            {
                it = que.begin();
            }
        }
        fa[i] = *it;
        *it = i; 
        it++;
        if (it == que.end())
        {
            it = que.begin();
        }
    }
    
    cout << "! ";
    for (int i = 1; i < n; i++)
    {
        cout << fa[i] << (i == n - 1 ? "" : " ");
    }
    cout << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--)
    {
        solved();
    }
    return 0;
}