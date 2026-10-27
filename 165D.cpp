#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
using i64 = long long;

// 支持取模的线段树模块
struct Segt
{
    struct node
    {
        int l, r; // 区间左右端点 [l, r]
        i64 w;    // 当前区间和 (已取模)
    };
    vector<node> tree; // 线段树节点数组，大小为 4N
    Segt() {}

#define GL (k << 1)     // 左儿子索引 2k
#define GR (k << 1 | 1) // 右儿子索引 2k + 1

    // 线段树初始化建树（包含取模参数）
    void init(int n)
    {
        tree.resize(n * 4 + 1);
        auto build = [&](auto self, int l, int r, int k = 1) -> void
        {
            tree[k] = {l, r, 0};
            if (l == r)
            {
                return;
            }
            int mid = (l + r) / 2;
            self(self, l, mid, GL);
            self(self, mid + 1, r, GR);
        };
        build(build, 1, n);
    }
    // 单点修改（替换掉缓慢的区间 modify 和 lazy）
    void update(int pos, int val, int k = 1)
    {
        if (tree[k].l == tree[k].r)
        {
            tree[k].w = val;
            return;
        }
        int mid = (tree[k].l + tree[k].r) / 2;
        if (pos <= mid)
            update(pos, val, GL);
        else
            update(pos, val, GR);
        tree[k].w = tree[GL].w + tree[GR].w; // pushup
    }

    int ask(int l, int r, int k = 1)
    {
        if (l > r)
            return 0; // 边界保护
        if (l <= tree[k].l && tree[k].r <= r)
        {
            return tree[k].w;
        }
        int mid = (tree[k].l + tree[k].r) / 2;
        int ans = 0;
        if (l <= mid)
            ans += ask(l, r, GL);
        if (mid < r)
            ans += ask(l, r, GR);
        return ans;
    }
};

// 树链剖分模块 (Heavy-Light Decomposition)
struct HLD
{
    int n, mod, idx;
    vector<vector<pair<int, int>>> adj; // 邻接表存图
    vector<int> siz, dep;               // siz: 子树大小, dep: 深度
    vector<int> top, son, father;       // top: 链顶, son: 重儿子, father: 父节点
    vector<int> dfn, rev_dfn;           // dfn: DFS序(DFN), rev_dfn: DFS序反查节点编号
    vector<i64> in, val;                // in: 原始点权, val: 按DFS序重排后的点权
    Segt segt;                          // 内部线段树实例
    vector<int> edge_to_node;

    // 构造函数：初始化大小与模数
    HLD(int n, int mod = 1e9 + 7)
    {
        this->n = n;
        this->mod = mod;
        edge_to_node.resize(n + 1);
        adj.resize(n + 1);
        siz.resize(n + 1);
        dep.resize(n + 1);
        top.resize(n + 1);
        son.resize(n + 1);
        father.resize(n + 1);
        idx = 0;
        in.resize(n + 1);
        dfn.resize(n + 1);
        rev_dfn.resize(n + 1);
        val.resize(n + 1);
    }

    // 邻接表加边
    void add(int x, int y, int e_id)
    {
        adj[x].push_back({y, e_id});
        adj[y].push_back({x, e_id});
    }

    // 第一次 DFS：求father、dep、siz与son
    void dfs1(int x)
    {
        siz[x] = 1;
        dep[x] = dep[father[x]] + 1;
        for (auto [y, e_id] : adj[x])
        {
            if (y == father[x])
                continue;
            father[y] = x;
            edge_to_node[e_id] = y;
            dfs1(y);
            siz[x] += siz[y];
            if (siz[y] > siz[son[x]])
            {
                son[x] = y; // 更新重儿子
            }
        }
    }

    // 第二次 DFS：剖分重链并生成 DFN 序
    void dfs2(int x, int up)
    {
        dfn[x] = ++idx;
        rev_dfn[idx] = x;
        val[idx] = in[x];
        top[x] = up;
        if (son[x])
            dfs2(son[x], up); // 优先遍历重儿子
        for (auto [y, e_id] : adj[x])
        {
            if (y == father[x] || y == son[x])
                continue;
            dfs2(y, y); // 遍历轻儿子
        }
    }
    // 路径查询 (pathSum)：求路径 u -> v 上所有节点权值和 (Mod MOD)
    i64 pathSum(int u, int v)
    {
        i64 ans = 0;
        while (top[u] != top[v])
        {
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);

            ans = (ans + segt.ask(dfn[top[u]], dfn[u])) % mod;
            u = father[top[u]];
        }
        if (dep[u] > dep[v])
            swap(u, v);
        if (u != v)
        {
            return (ans + segt.ask(dfn[u] + 1, dfn[v]));
        }
        return ans;
    }
    void set_black(int u)
    {
        int node = edge_to_node[u];
        segt.update(dfn[node], 0);
    }
    void set_white(int u)
    {
        int node = edge_to_node[u];
        segt.update(dfn[node], 1);
    }
    int get_lca(int u, int v)
    {
        while (top[u] != top[v])
        {
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);
            u = father[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }

    // 初始化入口（传入点权向量）
    void work(const vector<i64> &in_val, int root = 1)
    {
        assert((int)in_val.size() == n + 1);
        this->in = in_val;
        dfs1(root);
        dfs2(root, root);
        segt.init(n);
    }
    // 初始化入口（无点权，后手动赋值）
    void work(int root = 1)
    {
        dfs1(root);
        dfs2(root, root);
        segt.init(n);
    }
};
// 边权转点权 黑表示1 链接,白表示0 断开
void solved()
{
    int n;
    cin >> n;
    HLD hld(n);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        hld.add(u, v, i);
    }
    int root = 1;
    for (int i = 1; i <= n; i++)
    {
        if (hld.adj[i].size() > 2)
        {
            root = i;
            break;
        }
    }
    hld.work(root);
    int m;
    cin >> m;
    while (m--)
    {
        int c, u, v;
        cin >> c;
        if (c == 1)
        {
            cin >> u;
            hld.set_black(u);
        }
        else if (c == 2)
        {
            cin >> u;
            hld.set_white(u);
        }
        else if (c == 3)
        {
            cin >> u >> v;
            if (u == v)
            {
                cout << 0 << endl;
                continue;
            }
            int white_cnt = hld.pathSum(u, v);
            if (white_cnt > 0)
            {
                cout << "-1\n";
                continue;
            }
            int lca = hld.get_lca(u, v);
            int dist = hld.dep[u] + hld.dep[v] - 2 * hld.dep[lca];
            cout << dist << endl;
        }
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    solved();
}