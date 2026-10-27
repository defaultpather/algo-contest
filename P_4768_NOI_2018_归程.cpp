#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const int INF = 2e9 + 7;
struct Edge
{
    int u, v, l, a;
    bool operator<(const Edge &other) const
    {
        return a > other.a;
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
struct ShortestPath
{
    int n;
    vector<vector<pair<int, int>>> adj; // 原图邻接表：{邻居, 边长}
    vector<int> dist;                   // 1号点到各点的最短距离

    ShortestPath(int n) : n(n)
    {
        adj.resize(n + 1);
        dist.assign(n + 1, INF);
    }

    void add_edge(int u, int v, int w)
    {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void dijkstra(int start)
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        dist[start] = 0;
        pq.push({0, start});

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
                    pq.push({dist[v], v});
                }
            }
        }
    }
};
struct KruskalTree
{
    int n;                   // 原图点数
    int node_cnt;            // 重构树总结点数 (最多 2n - 1)
    vector<int> val;         // 重构树节点的权值（边海拔）
    vector<int> mindist;     // 子树内叶子节点到 1 号点的最短路最小值
    vector<vector<int>> adj; // 重构树的邻接表（父指向子）
    vector<vector<int>> ver; // 倍增祖先表
    vector<int> dep;         // 节点深度
    DSU dsu;                 // 内置并查集

    KruskalTree(int n) : n(n), node_cnt(n), dsu(2 * n)
    {
        val.resize(2 * n + 1, 0);
        mindist.resize(2 * n + 1, INF);
        adj.resize(2 * n + 1);
        dep.assign(2 * n + 1, 0);
        ver.resize(2 * n + 1, vector<int>(20, 0));
    }

    void build(vector<Edge> &edges)
    {
        sort(edges.begin(), edges.end()); // 按海拔降序排序
        for (auto &e : edges)
        {
            int fu = dsu.find(e.u);
            int fv = dsu.find(e.v);
            if (fu != fv)
            {
                int p = ++node_cnt; // 新建重构树节点
                val[p] = e.a;       // 记录海拔权值
                dsu.fa[fu] = p;     // 并查集根指向新节点
                dsu.fa[fv] = p;
                adj[p].push_back(fu); // 树边：父节点 -> 子节点
                adj[p].push_back(fv);
            }
        }
    }
    void dfs(int u, int fa, const vector<int> &dist)
    {
        dep[u] = dep[fa] + 1;
        ver[u][0] = fa;

        for (int i = 1; i <= __lg(dep[u]); i++)
        {
            ver[u][i] = ver[ver[u][i - 1]][i - 1];
        }

        // 叶节点初始值为 Dijkstra 求得的最短路，非叶节点初始化为 INF
        if (u <= n)
        {
            mindist[u] = dist[u];
        }
        else
        {
            mindist[u] = INF;
        }
        for (int v : adj[u])
        {
            dfs(v, u, dist);
            mindist[u] = min(mindist[u], mindist[v]);
        }
    }
    int query(int st, int limit)
    {
        for (int p = __lg(dep[st]); p >= 0; p--)
        {
            if (ver[st][p] > 0 && val[ver[st][p]] > limit)
            {
                st = ver[st][p];
            }
        }
        return mindist[st]; // 返回该连通块内到 1 号点的最短距离
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;

    ShortestPath sp(n);
    vector<Edge> edges(m);

    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].l >> edges[i].a;
        sp.add_edge(edges[i].u, edges[i].v, edges[i].l); 
    }

    sp.dijkstra(1);

    KruskalTree kt(n);
    kt.build(edges);
    kt.dfs(kt.node_cnt, 0, sp.dist);

    int q, k, s;
    cin >> q >> k >> s;
    int last_ans = 0;

    while (q--)
    {
        int v, p;
        cin >> v >> p;
        int v0 = (v + k * last_ans - 1) % n + 1;
        int p0 = (p + k * last_ans) % (s + 1);

        last_ans = kt.query(v0, p0);
        cout << last_ans << endl;
    }
}

int main()
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