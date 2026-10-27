#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int u, v, w;
    bool operator<(const Edge &x) const
    {
        return w < x.w; // 升序排序
    }
};
struct DSU
{
    int n;
    vector<int> fa;
    DSU(int n) : n(n)
    {
        fa.resize(n + 1);
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
struct KruskalTree
{
    int n;           // 原图点数
    int node_cnt;    // 重构树总结点数 (最多 2n - 1)
    vector<int> val; // 重构树上节点的权值
    vector<vector<int>> adj;//存重构树的图
    vector<vector<int>> ver; // 倍增祖先
    vector<int> dep;
    vector<bool> vis;
    DSU dsu;

    KruskalTree(int n) : n(n), node_cnt(n), dsu(2 * n)
    {
        val.resize(2 * n + 1, 0);
        adj.resize(2 * n + 1);
        dep.assign(2 * n + 1, 0);
        ver.resize(2 * n + 1, vector<int>(20, 0));
        vis.assign(2 * n + 1, false);
    }

    void build(vector<Edge> &edges)
    {
        sort(edges.begin(), edges.end());//最小化最大边
        for (auto &e : edges)
        {
            int fu = dsu.find(e.u);
            int fv = dsu.find(e.v);
            if (fu != fv)
            {
                int p = ++node_cnt;
                val[p] = e.w;
                dsu.fa[fu] = p;
                dsu.fa[fv] = p;
                adj[p].push_back(fu);
                adj[p].push_back(fv);
            }
        }
        // 处理可能不连通的森林情况
        for (int i = 1; i <= node_cnt; i++)
        {
            if (dsu.find(i) == i && !vis[i])
            {
                dfs(i, 0);
            }
        }
    }
    void dfs(int u, int fa)
    {
        vis[u] = true;
        dep[u] = dep[fa] + 1;
        ver[u][0] = fa;

        for (int i = 1; i <= __lg(dep[u]); i++)
        {
            ver[u][i] = ver[ver[u][i - 1]][i - 1];
        }
        for (int v : adj[u])
        {
            if (v == fa)
                continue;
            dfs(v, u);
        }
    }

    int lca(int u, int v)
    {
        if (dep[u] < dep[v])
            swap(u, v);
        while (dep[u] > dep[v])
        {
            u = ver[u][__lg(dep[u] - dep[v])];
        }
        if (u == v)
            return u;
        for (int k = __lg(dep[u]); k >= 0; k--)
        {
            if (ver[u][k] != ver[v][k])
            {
                u = ver[u][k];
                v = ver[v][k];
            }
        }
        return ver[u][0];
    }

    int query_max_edge(int x, int y)
    {
        if (dsu.find(x) != dsu.find(y))
            return -1; // 不连通
        int ancestor = lca(x, y);
        return val[ancestor];
    }
};
void solve()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin>>n>>m;
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    KruskalTree kt(n);
    kt.build(edges);
    int q;
    cin >> q;
    while (q--)
    {
        int x, y;
        cin >> x >> y;
        int ans = kt.query_max_edge(x, y);
        if (ans == -1)
        {
            cout << "impossible\n";
        }
        else
        {
            cout << ans << "\n";
        }
    }
}
int main()
{
    solve();
    return 0;
}