#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

struct Edge
{
    int u, v, w;
    bool operator<(const Edge &other) const
    {
        return w < other.w;
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
template <typename T, typename Compare = less<T>>
struct SparseTable
{
    int n;
    int max_log;
    Compare cmp;
    vector<T> a;          // 存储原始数据的副本 (1-indexed)
    vector<vector<T>> st; // st[i][j] 存储区间 [i, i + 2^j - 1] 的最值

    SparseTable() : n(0), max_log(0) {}

    SparseTable(const vector<T> &v, Compare comp = Compare()) : cmp(comp)
    {
        build(v);
    }

    void build(const vector<T> &v)
    {
        n = (int)v.size() - 1;
        if (n <= 0)
            return;

        a = v;
        max_log = __lg(n);
        st.assign(n + 1, vector<T>(max_log + 1, T()));
        for (int i = 1; i <= n; i++)
        {
            st[i][0] = a[i];
        }

        for (int j = 1; j <= max_log; j++)
        {
            for (int i = 1; i + (1 << j) - 1 <= n; i++)
            {
                T left_val = st[i][j - 1];
                T right_val = st[i + (1 << (j - 1))][j - 1];
                st[i][j] = cmp(left_val, right_val) ? left_val : right_val;
            }
        }
    }
    T query(int l, int r) const
    {
        int k = __lg(r - l + 1);
        T left_val = st[l][k];
        T right_val = st[r - (1 << k) + 1][k];
        return cmp(left_val, right_val) ? left_val : right_val;
    }
};
struct KruskalTree
{
    int n;                   // 原图点数
    int node_cnt;            // 重构树总结点数 (最多 2n - 1)
    int timer;               // DFN 时间戳计数器
    vector<int> val;         // 重构树节点的权值（边的编号)
    vector<int> dfn;         // 原图节点在重构树上的 DFN 序 
    vector<int> rev_dfn;     // DFN 序映射回重构树节点 (rev_dfn[dfn[u]] = u)
    vector<int> dep;         // 重构树节点的深度
    vector<vector<int>> adj; // 重构树邻接表（父指向子）
    vector<vector<int>> ver; // 树上倍增 LCA 数组
    DSU dsu;                 // 内置并查集

    KruskalTree(int n) : n(n), node_cnt(n), timer(0), dsu(2 * n)
    {
        val.resize(2 * n + 1, 0);
        dfn.resize(2 * n + 1, 0);
        rev_dfn.resize(2 * n + 1, 0);
        dep.assign(2 * n + 1, 0);
        adj.resize(2 * n + 1);
        ver.resize(2 * n + 1, vector<int>(20, 0));
    }

    void build(vector<Edge> &edges)
    {
        sort(edges.begin(), edges.end()); 
        for (auto &e : edges)
        {
            int fu = dsu.find(e.u);
            int fv = dsu.find(e.v);
            if (fu != fv)
            {
                int p = ++node_cnt; // 新建重构树节点
                val[p] = e.w;       // 记录边编号作为节点权值
                dsu.fa[fu] = p;     // 并查集合并
                dsu.fa[fv] = p;
                adj[p].push_back(fu); 
                adj[p].push_back(fv);
            }
        }
    }

    void dfs(int u, int fa)
    {
        dep[u] = dep[fa] + 1;
        dfn[u] = ++timer;
        rev_dfn[timer] = u;
        ver[u][0] = fa;

        for (int i = 1; i <= __lg(dep[u]); i++)
        {
            ver[u][i] = ver[ver[u][i - 1]][i - 1];
        }
        for (int v : adj[u])
        {
            dfs(v, u);
        }
    }
    int lca(int u, int v)
    {
        if (dep[u] < dep[v])
            swap(u, v);
        for (int i = __lg(dep[u]); i >= 0; i--)
        {
            if (dep[u] - (1 << i) >= dep[v])
            {
                u = ver[u][i];
            }
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
    }
};

void solve()
{
    int n, m, q;
    cin >> n >> m >> q;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].u >> edges[i].v;
        edges[i].w = i + 1; 
    }
    KruskalTree kt(n);
    kt.build(edges);

    kt.dfs(kt.node_cnt, 0);

    vector<int> dfn_val(n + 1);
    for (int i = 1; i <= n; i++)
    {
        dfn_val[i] = kt.dfn[i];
    }
    SparseTable<int, less<int>> st_min(dfn_val);
    SparseTable<int, greater<int>> st_max(dfn_val);
    for (int i = 0; i < q; i++)
    {
        int l, r;
        cin >> l >> r;
        if (l == r)
        {
            cout << 0 << (i == q - 1 ? "" : " ");
            continue;
        }

        int min_dfn = st_min.query(l, r);//这里查的是时间戳值
        int max_dfn = st_max.query(l, r);

        int u = kt.rev_dfn[min_dfn];//通过时间戳映射回原来的结点
        int v = kt.rev_dfn[max_dfn];

        int ans_lca = kt.lca(u, v);
        cout << kt.val[ans_lca] << (i == q - 1 ? "" : " ");
    }
    cout << endl;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}