#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

struct Node
{
    int l, r;
    mutable int v;
    bool operator<(const Node &a) const
    {
        return l < a.l;
    }
};
set<Node> odt;
auto split(int x)
{
    auto it = --odt.upper_bound({x, 0, 0});
    if (it->l == x)
        return it;
    int l = it->l, r = it->r, v = it->v;
    odt.erase(it);
    odt.insert({l, x - 1, v});
    return odt.insert({x, r, v}).first;
}

// 覆盖 [l, r] 为 val，同时返回覆盖前区间内 1 的总数
int assign(int l, int r, int val)
{
    auto itr = split(r + 1);
    auto itl = split(l);
    int cnt_ones = 0;
    for (auto it = itl; it != itr; ++it)
    {
        if (it->v == 1)
        {
            cnt_ones += (it->r - it->l + 1);
        }
    }
    odt.erase(itl, itr);
    odt.insert({l, r, val});
    return cnt_ones;
}
struct HLD
{
    int n, idx;
    vector<vector<int>> adj;
    vector<int> siz, dep, top, son, father, dfn;

    HLD(int n) : n(n), idx(0), adj(n + 5), siz(n + 5), dep(n + 5),
                 top(n + 5), son(n + 5), father(n + 5), dfn(n + 5) {}

    void add(int x, int y)
    {
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

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
                son[x] = y;
        }
    }

    void dfs2(int x, int up)
    {
        dfn[x] = ++idx;
        top[x] = up;
        if (son[x])
            dfs2(son[x], up);
        for (auto y : adj[x])
        {
            if (y == father[x] || y == son[x])
                continue;
            dfs2(y, y);
        }
    }

    int install(int x)
    {
        int old_ones = 0;
        int u = x, v = 1;
        while (top[u] != top[v])
        {
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);
            old_ones += assign(dfn[top[u]], dfn[u], 1);
            u = father[top[u]];
        }
        if (dep[u] > dep[v])
            swap(u, v);
        old_ones += assign(dfn[u], dfn[v], 1);//一定是dfn序
        return dep[x] - old_ones;
    }

    int uninstall(int x)
    {
        return assign(dfn[x], dfn[x] + siz[x] - 1, 0);
    }

    void work(int root = 1)
    {
        dfs1(root);
        dfs2(root, root);
        odt.insert({1, n, 0});
        odt.insert({n + 1, n + 1, 0});
    }
};

void solve()
{
    int n;
    cin >> n;
    HLD hld(n);
    for (int i = 1, u; i < n; i++)
    {
        cin >> u;
        hld.add(u + 1, i + 1);
    }
    hld.work(1);

    int q;
    cin >> q;
    while (q--)
    {
        string type;
        int x;
        cin >> type >> x;
        x++; 
        if (type == "install")
        {
            cout << hld.install(x) << endl;
        }
        else
        {
            cout << hld.uninstall(x) << endl;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}