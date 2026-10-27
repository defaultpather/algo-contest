#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

struct SegmentTree
{
    struct node
    {
        int l, r, w, lazy;
    };
    vector<int> w;
    vector<node> t;
    SegmentTree() {}

#define GL (k << 1)
#define GR (k << 1 | 1)

    void init(vector<int> in)
    {
        int n = in.size() - 1;
        w.resize(n + 1);
        t.resize(n * 4 + 1);

        auto build = [&](auto self, int l, int r, int k = 1)
        {
            if (l == r)
            {
                t[k] = {l, r, 0, -1}; // 初始化为 0，lazy 初始为 -1 表示无标记
                return;
            }
            t[k] = {l, r, 0, -1};
            int mid = (l + r) / 2;
            self(self, l, mid, GL);
            self(self, mid + 1, r, GR);
            pushup(k);
        };
        build(build, 1, n);
    }

    void pushdown(node &p, int lazy)
    {
        p.w = (p.r - p.l + 1) * lazy; // 区间覆盖计算
        p.lazy = lazy;
    }

    void pushdown(int k)
    {
        if (t[k].lazy == -1) // -1 表示当前没有未下传的覆盖标记
            return;
        pushdown(t[GL], t[k].lazy);
        pushdown(t[GR], t[k].lazy);
        t[k].lazy = -1;
    }

    void pushup(int k)
    {
        t[k].w = t[GL].w + t[GR].w;
    }

    void modify(int l, int r, int val, int k = 1)
    {
        if (l <= t[k].l && t[k].r <= r)
        {
            pushdown(t[k], val);
            return;
        }
        pushdown(k);
        int mid = (t[k].l + t[k].r) / 2;
        if (l <= mid)
            modify(l, r, val, GL);
        if (mid < r)
            modify(l, r, val, GR);
        pushup(k);
    }

    int ask(int l, int r, int k = 1)
    {
        if (l <= t[k].l && t[k].r <= r)
        {
            return t[k].w;
        }
        pushdown(k);
        int mid = (t[k].l + t[k].r) / 2;
        int ans = 0;
        if (l <= mid)
            ans += ask(l, r, GL);
        if (mid < r)
            ans += ask(l, r, GR);
        return ans;
    }
};

struct HLD
{
    int n, idx;
    vector<vector<int>> adj;
    vector<int> siz, dep;
    vector<int> top, son, parent;
    vector<int> in, id, val;
    SegmentTree segt;

    HLD(int n)
    {
        this->n = n;
        adj.resize(n + 1);
        siz.resize(n + 1);
        dep.resize(n + 1);
        top.resize(n + 1);
        son.resize(n + 1);
        parent.resize(n + 1);
        idx = 0;
        in.resize(n + 1);
        id.resize(n + 1);
        val.resize(n + 1);
    }

    void add(int x, int y)
    {
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    void dfs1(int x)
    {
        siz[x] = 1;
        dep[x] = dep[parent[x]] + 1;
        for (auto y : adj[x])
        {
            if (y == parent[x])
                continue;
            parent[y] = x;
            dfs1(y);
            siz[x] += siz[y];
            if (siz[y] > siz[son[x]])
            {
                son[x] = y;
            }
        }
    }

    void dfs2(int x, int up)
    {
        id[x] = ++idx;
        val[idx] = in[x];
        top[x] = up;

        if (son[x])
            dfs2(son[x], up);

        for (auto y : adj[x])
        {
            if (y == parent[x] || y == son[x])
                continue;
            dfs2(y, y);
        }
    }

    // 路径修改
    void modify(int l, int r, int val)
    {
        while (top[l] != top[r])
        {
            if (dep[top[l]] < dep[top[r]])
                swap(l, r);

            segt.modify(id[top[l]], id[l], val);
            l = parent[top[l]];
        }
        if (dep[l] > dep[r])
            swap(l, r);

        segt.modify(id[l], id[r], val);
    }

    // 子树修改
    void modify_subtree(int root, int val)
    {
        segt.modify(id[root], id[root] + siz[root] - 1, val);
    }

    // 单点查询
    int ask_point(int v)
    {
        return segt.ask(id[v], id[v]);
    }

    void work(const vector<int> &in, int root = 1)
    {
        assert(in.size() == n + 1);
        this->in = in;
        dfs1(root);
        dfs2(root, root);
        segt.init(val);
    }
};

void solved()
{
    int n;
    cin>>n;
    HLD hld(n);
    vector<int> a(n + 1, 0);

    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        hld.add(u, v);
    }

    hld.work(a, 1);

    int q;
    cin >> q;
    while (q--)
    {
        int c, v;
        cin >> c >> v;
        if (c == 1)
        {
            hld.modify_subtree(v, 1);
        }
        else if (c == 2)
        {
            hld.modify(1, v, 0);
        }
        else
        {
            cout << hld.ask_point(v) << endl;
        }
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    while (T--)
    {
        solved();
    }
    return 0;
}