#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

#define endl '\n'
#define int long long

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<array<int, 2>> dp(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> dp[i][1];
    }
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    auto dfs = [&](this auto self, int u, int fa) -> void
    {
        for (auto v : adj[u])
        {
            if (v != fa)
            {
                self(v, u);
                dp[u][1] += dp[v][0];
                dp[u][0] += max(dp[v][1], dp[v][0]);
            }
        }
    };
    dfs(1, 0);
    cout << max(dp[1][0], dp[1][1]) << endl;
    return 0;
}
