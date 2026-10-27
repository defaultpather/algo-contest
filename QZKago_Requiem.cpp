#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

#define int long long
const int INF = 1e18;
struct node
{
    int v,w;
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<node>> adj(n);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    vector<int> dist(n, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for (int i = 0; i < m; i++){
        int s;
        cin >> s;
        s--;
        dist[s] = 0;
        pq.push({0, s});
    }
    while (!pq.empty()){
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]){
            continue;
        }
        for (auto [v, w] : adj[u]){
            if (dist[v] > d + w){
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        ans = max(ans, dist[i]);
    }
    cout << ans + 1 << '\n';
}
