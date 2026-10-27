#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
using i64 = long long;

struct SegmentTree
{
    struct node
    {
        int l, r; // 区间左右端点 [l, r]
        i64 w;    // 当前区间和 (已取模)
        i64 lazy; // 懒标记（待下传的加法值，已取模）
    };
    int n;
    vector<i64> w;     // 存储按 DFN 序排列后的初始点权
    vector<node> tree; // 线段树节点数组，大小为 4N
    SegmentTree() {}

#define GL (k << 1)     // 左儿子索引 2k
#define GR (k << 1 | 1) // 右儿子索引 2k + 1

    void init(int n)
    {
        this->n = n;
        tree.resize(n * 4 + 1);
        auto build = [&](auto self, int l, int r, int k = 1) -> void
        {
            if (l == r)
            {
                tree[k] = {l, r, 0};
                return;
            }
            tree[k] = {l, r, 0};
            int mid = (l + r) / 2;
            self(self, l, mid, GL);
            self(self, mid + 1, r, GR);
            pushup(k);
        };
        build(build, 1, n);
    }
    // 单节点懒标记作用逻辑
    void pushdown(node &p, i64 lazy_val)
    {
        p.w = p.w + (p.r - p.l + 1) * lazy_val;
        p.lazy = p.lazy + lazy_val;
    }
    // 懒标记下传给左右儿子
    void pushdown(int k)
    {
        if (tree[k].lazy == 0)
            return;
        pushdown(tree[GL], tree[k].lazy);
        pushdown(tree[GR], tree[k].lazy);
        tree[k].lazy = 0;
    }
    void pushup(int k)
    {
        tree[k].w = tree[GL].w + tree[GR].w;
    }

    // 单点修改：在位置 pos 上增加 val（无需懒标记） k表示默认从根开始当前所在的节点位置
    void modify(int pos, i64 val, int k = 1)
    {
        if (tree[k].l == tree[k].r)
        {
            tree[k].w += val; // 到达目标叶子节点，更新权值（覆盖可改写为 tree[k].w = val）
            return;
        }
        int mid = (tree[k].l + tree[k].r) / 2; // 当前到达区间的中点
        if (pos <= mid)
            modify(pos, val, GL); // 目标点在左半区
        else
            modify(pos, val, GR); // 目标点在右半区
        pushup(k);                // 回溯时向上更新祖先节点的和
    }

    // 目标区间修改：[l, r] 加 val
    void modify(int l, int r, i64 val, int k = 1) // k表示当前所在的结点位置
    {
        if (l <= tree[k].l && tree[k].r <= r)
        {
            pushdown(tree[k], val);
            return;
        }
        pushdown(k);
        int mid = (tree[k].l + tree[k].r) / 2;
        if (l <= mid)
            modify(l, r, val, GL);
        if (mid < r)
            modify(l, r, val, GR);
        pushup(k);
    }

    // 目标区间查询：求 [l, r] 权值和
    i64 ask(int l, int r, int k = 1)
    {
        if (l > r)
            return 0;
        if (l <= tree[k].l && tree[k].r <= r)
        {
            return tree[k].w;
        }
        pushdown(k);
        int mid = (tree[k].l + tree[k].r) / 2;
        i64 ans = 0;
        if (l <= mid)
            ans = ans + ask(l, r, GL);
        if (mid < r)
            ans = ans + ask(l, r, GR);
        return ans;
    }
};
// 树链剖分模块 (Heavy-Light Decomposition)
struct HLD
{
    int n, mod, idx;
    vector<vector<int>> adj;      // 邻接表存图
    vector<int> siz, dep;         // siz: 子树大小, dep: 深度
    vector<int> top, son, father; // top: 链顶, son: 重儿子, father: 父节点
    vector<int> dfn, rev_dfn;     // dfn: DFS序(DFN), rev_dfn: DFS序反查节点编号
    vector<int> in, val;          // in: 原始点权, val: 按DFS序重排后的点权
    SegmentTree segt;             // 内部线段树实例

    // 构造函数：初始化大小与模数
    HLD(int n, int mod = 1e9 + 7)
    {
        this->n = n;
        this->mod = mod;
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
    void add(int x, int y)
    {
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    // 第一次 DFS：求father、dep、siz与son
    void dfs1(int x)
    {
        siz[x] = 1;
        dep[x] = dep[father[x]] + 1;
        for (auto y : adj[x])
        {
            if (y == father[x])
                continue;
            father[y] = x;
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
        for (auto y : adj[x])
        {
            if (y == father[x] || y == son[x])
                continue;
            dfs2(y, y); // 遍历轻儿子
        }
    }
    // 路径修改 (pathAdd)：路径 u -> v 上所有节点权值加上 val
    void pathAdd(int u, int v, i64 val)
    {
        while (top[u] != top[v])
        {
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);
            segt.modify(dfn[top[u]], dfn[u], val);
            u = father[top[u]];
        }
        if (dep[u] > dep[v])
            swap(u, v);
        segt.modify(dfn[u] + 1, dfn[v], val);
    }
    i64 query(int u, int v)
    {
        if (dep[u] < dep[v])
        {
            swap(u, v);
        }
        return segt.ask(dfn[u], dfn[u]);
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

        return (ans + segt.ask(dfn[u], dfn[v])) % mod; // 找到最后同一段重链后,最后的那一段求和
    }
    // 初始化入口（无点权，后手动赋值）
    void work(int n, int root = 1)
    {
        dfs1(root);
        dfs2(root, root);
        segt.init(n);
    }
};
void solved()
{
    int n, m;
    cin >> n >> m;
    HLD hld(n);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        hld.add(u, v);
    }
    hld.work(n);
    char type;
    int u, v;
    while (m--)
    {
        cin >> type >> u >> v;
        if (type == 'P')
        {
            hld.pathAdd(u, v, 1);
        }
        else if (type == 'Q')
        {
            cout << hld.query(u, v) << endl;
        }
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // cin>>T;
    while (T--)
    {
        solved();
    }
    return 0;
}
