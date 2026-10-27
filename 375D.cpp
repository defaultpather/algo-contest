#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

struct Query
{
    int k, id;
};

template <typename T = int>
struct TreeDSU
{
    int n;
    vector<T> arr; // 节点权值/颜色
    vector<vector<int>> adj;
    // 树结构与 DFN 序
    vector<int> fa, dep, siz, son;
    vector<int> dfn, rev_dfn;
    int cntd;

    vector<int> cnt; // 统计颜色频次
    vector<int> sum; // sum[i] 表示颜色数量大于等于 i 的有几种

    vector<vector<Query>> queries; // queries[u] 存储节点 u 上的询问
    vector<int> ans;               // ans[id] 存储编号为 id 的询问的答案
    TreeDSU(int n_, int q_, int max_val = 1000100) : n(n_), cntd(0)
    {
        arr.resize(n + 1);
        adj.resize(n + 1);

        fa.resize(n + 1);
        dep.resize(n + 1);
        siz.resize(n + 1);
        son.resize(n + 1);
        dfn.resize(n + 1);
        rev_dfn.resize(n + 1);

        // cnt.resize(max_val + 1, 0);
        sum.resize(n + 1, 0);

        queries.resize(n + 1);
        ans.resize(q_ + 1, 0);
    }
    void initCnt(int max_val){
        cnt.resize(max_val+1,0);
    }
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void addQuery(int u, int k, int id)
    {
        queries[u].push_back({k, id});
    }

    void dfs1(int u, int f)
    {
        fa[u] = f;
        dep[u] = dep[f] + 1;
        siz[u] = 1;
        son[u] = 0;
        dfn[u] = ++cntd;
        rev_dfn[cntd] = u;

        for (auto v : adj[u])
        {
            if (v != f)
            {
                dfs1(v, u);
                siz[u] += siz[v];
                if (son[u] == 0 || siz[v] > siz[son[u]])
                {
                    son[u] = v;
                }
            }
        }
    }
    void effect(int u){
        cnt[arr[u]]++;
        sum[cnt[arr[u]]]++;
        for(auto v:adj[u]){
            if(v!=fa[u]){
                effect(v);
            }
        }
    }
    void cancel(int u)
    {
        sum[cnt[arr[u]]]--;
        cnt[arr[u]]--;
        for(auto v:adj[u]){
            if(v!=fa[u]){
                cancel(v);
            }
        }
    }
    void dfs2(int u, int keep)
    {
        // 1. 先遍历轻儿子
        for (auto v : adj[u])
        {
            if (v != fa[u] && v != son[u])
            {
                dfs2(v, 0);
            }
        }
        // 2. 遍历重儿子（保留状态）
        if (son[u] != 0)
        {
            dfs2(son[u], 1);
        }
        // effect(u); // 加入节点 u 自身贡献
        cnt[arr[u]]++;
        sum[cnt[arr[u]]]++;
        for (auto v : adj[u])
        { // 重新计算每个轻子树的贡献
            if (v != fa[u] && v != son[u])
            {
                effect(v);
            }
        }
        // 4. 当场回答节点 u 上的所有离线询问 (O(1) 回答)
        for (auto &q : queries[u])
        {
            if (q.k > n)
                ans[q.id] = 0; // 特判 k > n 越界情况
            else
                ans[q.id] = sum[q.k];
        }
        if (keep == 0)
        {
            cancel(u);
        }
    }
    void work(int root = 1)
    {
        dfs1(root, 0);
        dfs2(root, 0);
    }
};
void solved()
{
    int n, m;
    cin>>n>>m;
    TreeDSU td(n, m);
    int max_c = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> td.arr[i];
        max_c = max(max_c, td.arr[i]); // 找出颜色最大值
    }
    td.initCnt(max_c);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        td.addEdge(u, v);
    }
    for (int i = 1; i <= m; i++)
    {
        int v, k;
        cin >> v >> k;
        td.addQuery(v, k, i);
    }
    td.work(1);
    for (int i = 1; i <= m; i++)
    {
        cout << td.ans[i] << endl;
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