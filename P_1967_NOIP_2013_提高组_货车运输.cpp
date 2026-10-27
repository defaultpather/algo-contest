#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

#define endl '\n'

// 边的结构体定义
struct Edge
{
    int u, v, w;
    bool operator<(const Edge &other) const
    {
        return w > other.w; // 按边权降序排列，用于 Kruskal 算法构建最大生成树
    }
};

// 并查集结构体：用于 Kruskal 连通性判断及查询两点是否连通
struct DSU
{
    vector<int> parent;
    DSU(int n) : parent(n + 1)
    {
        iota(parent.begin(), parent.end(), 0); // 初始化 parent[i] = i
    }
    int find(int i)
    {
        if (i != parent[i])
        {
            parent[i] = find(parent[i]);
        }
        return parent[i];
    }
    bool unite(int u, int v)
    {
        int rootU = find(u), rootV = find(v);
        if (rootU != rootV)
        {
            parent[rootU] = rootV;
            return true;
        }
        return false;
    }
};

// 基于倍增 LCA 的最大生成森林结构体
struct Tree
{
    int n;
    struct TreeEdge
    {
        int to, w;
    };
    vector<vector<TreeEdge>> adj; // 树的邻接表
    vector<vector<int>> val;      // val[x][i] : x 向上跳 2^i 步到达的祖先节点
    vector<vector<int>> min_w;    // min_w[x][i] : x 向上跳 2^i 步路径上的最小边权（瓶颈权值）
    vector<int> dep;              // dep[x] : 节点 x 的深度
    vector<bool> vis;             // 标记节点是否已访问（处理森林情况）
    DSU dsu;                      // 维护连通块信息

    Tree(int n) : n(n), dsu(n)
    {
        adj.resize(n + 1);
        val.resize(n + 1, vector<int>(20, 0));
        min_w.resize(n + 1, vector<int>(20, 1e9)); // 路径瓶颈取 min，初始设为极大值
        dep.resize(n + 1, 0);
        vis.resize(n + 1, false);
    }

    void add_edge(int u, int v, int w)
    {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // DFS 预处理：维护节点深度、倍增祖先 val 以及倍增最小边权 min_w
    void dfs(int x, int fa, int edge_w)
    {
        vis[x] = true;
        val[x][0] = fa;
        min_w[x][0] = edge_w;
        dep[x] = dep[fa] + 1;

        // 递推倍增表：结合 __lg    位运算控制最大可能层数
        for (int i = 1; i <= __lg(dep[x]); i++){
            val[x][i] = val[val[x][i - 1]][i - 1];
            min_w[x][i] = min(min_w[x][i - 1], min_w[val[x][i - 1]][i - 1]);
        }

        for (const auto &edge : adj[x])
        {
            if (edge.to == fa)
                continue;
            dfs(edge.to, x, edge.w);
        }
    }

    // 初始化 DFS（考虑非连通图/森林的情况）
    void build_forest()
    {
        for (int i = 1; i <= n; i++)///防止是森林的话,有的不会处理到
        {
            if (!vis[i])
            {
                dfs(i, 0, 1e9);
            }
        }
    }

    // LCA 倍增查询：返回两点路径上的最大载流量（即路径最小边权）
    int query_min_edge(int x, int y)
    {
        // 若两点不在同一个连通分量中，无法到达，返回 -1
        if (dsu.find(x) != dsu.find(y))
            return -1;

        int ans = 1e9;

        // 1. 确保 x 是深度较深的节点
        if (dep[x] < dep[y])
            swap(x, y);

        // 2. 将 x 提升至与 y 相同的深度，同时更新路径上的最小边权
        while (dep[x] > dep[y])
        {
            int k = __lg(dep[x] - dep[y]);
            ans = min(ans, min_w[x][k]);
            x = val[x][k];
        }

        if (x == y)
            return ans;

        // 3. x 和 y 同步向上跳跃，寻找 LCA 正下方节点
        for (int k = __lg(dep[x]); k >= 0; k--)
        {
            if (val[x][k] != val[y][k])
            {
                ans = min({ans, min_w[x][k], min_w[y][k]});
                x = val[x][k];
                y = val[y][k];
            }
        }

        // 最后跨越一步到达 LCA，统计最后两跳的边权
        ans = min({ans, min_w[x][0], min_w[y][0]});
        return ans;
    }
};

int main()
{
    // 快速 IO 优化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m))
        return 0;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    // 1. Kruskal 贪心算法：生成最大生成树 (森林)
    sort(edges.begin(), edges.end());

    Tree tree(n);
    for (const auto &edge : edges)
    {
        if (tree.dsu.unite(edge.u, edge.v))
        {
            tree.add_edge(edge.u, edge.v, edge.w);
        }
    }

    // 2. 在最大生成森林上运行 DFS 进行倍增预处理
    tree.build_forest();

    // 3. 处理 Q 次询问
    int q;
    cin >> q;
    while (q--)
    {
        int u, v;
        cin >> u >> v;
        cout << tree.query_min_edge(u, v) << endl;
    }

    return 0;
}