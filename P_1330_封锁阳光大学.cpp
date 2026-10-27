#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long
int color[100100];
vector<int> adj[100100];
int w = 0, g = 0;
bool dfs(int u, int c)
{
    color[u] = c;
    if (c & 1)
        w++;
    else
        g++;
    for (auto v : adj[u])
    {
        if (!color[v])
        {
            if (dfs(v, 3 - c))
                return 1;
        }
        else if (color[v] == c)
        {
            return 1;
        }
    }
    return 0;
}
void solved()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    bool ok = 0;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (!color[i])
        {
            w = g = 0;
            if (dfs(i, 1))
            {
                ok = 1;
                break;
            }
            else
            {
                ans += min(w, g);
            }
        }
    }
    if (ok)
    {
        cout << "Impossible\n";
        return;
    }
    else
    {
        cout << ans << endl;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // cin>>T;
    while (T--)
    {
        solved();
    }
    return 0;
}
