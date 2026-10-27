#include <bits/stdc++.h>
using namespace std;

// 原始边结构
struct RawEdge
{
    int u, v;
    long long w;
    int id; // 边的原始编号 1 ~ m
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
    int n;                   // 原图点数
    int node_cnt;            // 重构树总结点数
    vector<long long> val;   // 重构树节点的权值
    vector<vector<int>> adj; // 重构树邻接表
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

    // 按边的编号 1~m 顺序构建重构树
    void build(const vector<RawEdge> &edges, vector<bool> &is_tree_edge)
    {
        int m = edges.size();
        for (int i = 0; i < m; i++)
        {
            int u = edges[i].u;
            int v = edges[i].v;
            long long w = edges[i].w;

            int fu = dsu.find(u);
            int fv = dsu.find(v);

            if (fu != fv)
            {
                is_tree_edge[i] = true; // 标记为重构树边
                int p = ++node_cnt;
                val[p] = w; // 点权设为当前边的权值
                dsu.fa[fu] = p;
                dsu.fa[fv] = p;
                adj[p].push_back(fu);
                adj[p].push_back(fv);
            }
            else
            {
                is_tree_edge[i] = false; // 非树边
            }
        }

        // 处理重构树的 DFS 和倍增表
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

    // 查询非树边 u-v 在重构树上的 LCA 点权（即传送代价）
    long long query_lca_val(int x, int y)
    {
        int ancestor = lca(x, y);
        return val[ancestor];
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<RawEdge> edges(m);
    long long total_edge_sum = 0;

    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].id = i + 1;
        total_edge_sum += edges[i].w; // 1. 所有边权的固定基础消耗
    }

    if (m == 0)
    {
        cout << 0 << "\n";
        return;
    }

    KruskalTree kt(n);
    vector<bool> is_tree_edge(m, false);

    // 2. 按编号顺序（即输入顺序）建重构树
    kt.build(edges, is_tree_edge);

    long long extra_teleport_cost = 0;

    // 3. 计算所有非树边的传送额外开销
    for (int i = 0; i < m; i++)
    {
        if (!is_tree_edge[i])
        {
            int u = edges[i].u;
            int v = edges[i].v;
            if (u != v)
            { // 自环特判：若 u==v，直接在 u 点传送，代价为当前边权 w
                extra_teleport_cost += kt.query_lca_val(u, v);
            }
            else
            {
                extra_teleport_cost += edges[i].w;
            }
        }
    }

    cout << total_edge_sum + extra_teleport_cost << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t)
    {
        while (t--)
        {
            solve();
        }
    }
    return 0;
}