#include <bits/stdc++.h>
using namespace std;

#define int long long

void solved()
{
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> sz(n + 1);
    vector<int> f(n + 1);
    auto dfs1 = [&](this auto &&dfs1, int u, int fa) -> void
    {
        sz[u] = 1;
        for (auto v : adj[u])
        {
            if (v != fa)
            {
                dfs1(v, u);
                sz[u] += sz[v];
                f[u] += f[v]; // 循环内添加儿子贡献
            }
        }
        // 只有递归返回的时候执行
        f[u] += sz[u];
    };
    vector<int> g(n + 1);
    int ans = 0;
    auto dfs2 = [&](this auto &&dfs2, int u, int fa) -> void
    {
        if (u != 1)
        {
            g[u] = g[fa] + n - 2 * sz[u];
            ans = max(ans, g[u]);
        }
        for (auto v : adj[u])
        {
            if (v != fa)
            {
                dfs2(v, u);
            }
        }
    };
    dfs1(1, 0);
    ans = g[1] = f[1];
    dfs2(1, 0);
    cout << ans <<"\n";
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T = 1;
    // cin>>T;
    while (T--)
    {
        solved();
    }
}