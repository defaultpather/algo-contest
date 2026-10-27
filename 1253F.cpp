#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = 1e18;

struct Edge
{
    int u, v;
    ll w;
    bool operator<(const Edge &other) const
    {
        return w < other.w;
    }
};

struct DSU
{
    vector<int> fa;
    DSU(int n) : fa(n + 1)
    {
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int u)
    {
        return fa[u] == u ? u : fa[u] = find(fa[u]);
    }
    bool merge(int u, int v)
    {
        u = find(u);
        v = find(v);
        if (u != v)
        {
            fa[u] = v;
            return true;
        }
        return false;
    }
};

void solve()
{
    int n, m, k, q;
    cin >> n >> m >> k >> q;

    vector<vector<pair<int, ll>>> adj(n + 1);
    vector<Edge> raw_edges(m);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        raw_edges[i] = {u, v, w};
    }

    vector<ll> dist(n + 1, INF);
    vector<int> belong(n + 1, 0);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

    for (int i = 1; i <= k; i++)
    {
        dist[i] = 0;
        belong[i] = i;
        pq.push({0, i});
    }

    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u])
            continue;

        for (auto &[v, w] : adj[u])
        {
            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                belong[v] = belong[u];
                pq.push({dist[v], v});
            }
        }
    }
    vector<Edge> new_edges;
    for (auto &e : raw_edges)
    {
        if (belong[e.u] != belong[e.v])
        {
            new_edges.push_back({belong[e.u], belong[e.v], dist[e.u] + dist[e.v] + e.w});
        }
    }

    sort(new_edges.begin(), new_edges.end());

    int node_cnt = k;
    vector<ll> val(2 * k + 1, 0);
    vector<vector<int>> tree(2 * k + 1);
    DSU dsu(2 * k);

    for (auto &e : new_edges)
    {
        int fu = dsu.find(e.u);
        int fv = dsu.find(e.v);
        if (fu != fv)
        {
            int p = ++node_cnt;
            val[p] = e.w;
            dsu.fa[fu] = p;
            dsu.fa[fv] = p;
            tree[p].push_back(fu);
            tree[p].push_back(fv);
        }
    }

    vector<int> dep(2 * k + 1, 0);
    vector<vector<int>> ver(2 * k + 1, vector<int>(20, 0));

    auto dfs = [&](auto self, int u, int fa) -> void
    {
        dep[u] = dep[fa] + 1;
        ver[u][0] = fa;
        for (int i = 1; i <= __lg(dep[u]); i++)
        {
            ver[u][i] = ver[ver[u][i - 1]][i - 1];
        }
        for (int v : tree[u])
        {
            self(self, v, u);
        }
    };

    dfs(dfs, node_cnt, 0);

    auto lca = [&](int u, int v) -> int
    {
        if (dep[u] < dep[v])
            swap(u, v);
        for (int i = __lg(dep[u]); i >= 0; i--)
        {
            if (dep[u] - (1 << i) >= dep[v])
                u = ver[u][i];
        }
        if (u == v)
            return u;
        for (int i = __lg(dep[u]); i >= 0; i--)
        {
            if (ver[u][i] != ver[v][i])
            {
                u = ver[u][i];
                v = ver[v][i];
            }
        }
        return ver[u][0];
    };

    while (q--)
    {
        int a, b;
        cin >> a >> b;
        int ans_node = lca(a, b);
        cout << val[ans_node] << endl;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}