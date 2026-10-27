#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

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

    // 业务统计变量
    vector<int> colorCnt; // 颜色频次统计
    vector<int> ans;      // 节点子树查询答案
    vector<int>maxcnt;
    TreeDSU(int n_, int max_val = 100010) : n(n_), cntd(0)
    {
        arr.resize(n + 1);
        adj.resize(n + 1);

        fa.resize(n + 1);
        dep.resize(n + 1);
        siz.resize(n + 1);
        son.resize(n + 1);
        dfn.resize(n + 1);
        rev_dfn.resize(n + 1);

        colorCnt.assign(max_val + 1, 0);
        maxcnt.resize(max_val+1,0);
        ans.resize(n + 1);
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // DFS1(树剖过程)：维护 fa, dep, siz, son 及 dfn 序
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
    void effect(int u,int h)
    {
        ++colorCnt[arr[u]];
        if (colorCnt[arr[u]] == maxcnt[h])
        {
            ans[h] += arr[u];
        }
        else if (colorCnt[arr[u]] > maxcnt[h])
        {
            maxcnt[h] = colorCnt[arr[u]];
            ans[h] = arr[u];
        }
        for (auto v : adj[u])
        {
            if (v != fa[u])
            {
                effect(v,h);
            }
        }
    }
    void cancel(int u)
    {
        colorCnt[arr[u]] = 0;
        maxcnt[colorCnt[arr[u]]]=0;
        for (auto v : adj[u])
        {
            if (v != fa[u])
            {
                cancel(v);
            }
        }
    }
    // 启发式合并过程
    void dfs2(int u, int keep)
    {
        for (auto v : adj[u])
        {
            if (v != fa[u] && v != son[u])
            {
                dfs2(v, 0); // 先遍历轻儿子
            }
        }
        if (son[u] != 0)
        { // 遍历重儿子
            dfs2(son[u], 1);
        }
        maxcnt[u]=maxcnt[son[u]];
        ans[u]=ans[son[u]];
        ++colorCnt[arr[u]];
        if(colorCnt[arr[u]]==maxcnt[u]){
            ans[u]+=arr[u];
        }else if(colorCnt[arr[u]]>maxcnt[u]){
            maxcnt[u]=colorCnt[arr[u]];
            ans[u]=arr[u];
        }
        for (auto v : adj[u])
        { // 重新计算每个轻子树的贡献
            if (v != fa[u] && v != son[u])
            {
                effect(v,u);
            }
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
void solved(){
    int n;
    cin>>n;
    TreeDSU td(n);
    for(int i=1;i<=n;i++){
        cin>>td.arr[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        td.addEdge(u,v);
    }
    td.work(1);
    for(int i=1;i<=n;i++){
        cout<<td.ans[i]<< " \n"[i==n];
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T=1;
    // cin>>T;
    while(T--){
       solved();
    }
    return 0;
}
