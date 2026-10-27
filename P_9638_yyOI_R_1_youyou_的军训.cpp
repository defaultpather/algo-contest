#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
// #define int long long

struct Edge{
    int u,v,w,i;
    bool operator<(const Edge& e){
        return this->w>e.w;
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
const int MAXM=400010;
int edge_to_tree[MAXM];//原始边遍号对应树上的哪个虚结点的编号
int pend_edge[MAXM];//待修改的边编号
int pend_val[MAXM];//待修改的边对应的权值
int cnt_pend;

struct KruskalTree
{
    int n;                   // 原图点数
    int node_cnt;            // 重构树总结点数 (最多 2n - 1)
    vector<int> val;         // 重构树上节点的权值
    vector<vector<int>> adj; // 存重构树的图
    vector<vector<int>> ver; // 倍增祖先
    vector<int> dep;
    vector<bool> vis;
    vector<int>son_sz;//原图中的子树的子节点数
    DSU dsu;

    KruskalTree(int n) : n(n), node_cnt(n), dsu(2 * n)
    {
        val.resize(2 * n + 1, 0);
        adj.resize(2 * n + 1);
        dep.assign(2 * n + 1, 0);
        ver.resize(2 * n + 1, vector<int>(20, 0));
        vis.assign(2 * n + 1, false);
        son_sz.assign(2*n+1,0);
    }

    void build(vector<Edge> &edges)//建树函数
    {
        sort(edges.begin()+1, edges.end()); //最大化最小边
        for (auto &[u,v,w,i]: edges)
        {
            int fu = dsu.find(u);
            int fv = dsu.find(v);
            if (fu != fv)
            {
                int p = ++node_cnt;//新的虚结点编号
                edge_to_tree[i]=node_cnt;
                val[p] = w;
                dsu.fa[fu] = p;
                dsu.fa[fv] = p;
                adj[p].push_back(fu);
                adj[p].push_back(fv);
            }
        }
        // 处理可能不连通的森林情况
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
        if(u<=n){
            son_sz[u]=1;
        }else{
            son_sz[u]=0;
        }
        for(auto v:adj[u]){
            if(v==fa)continue;
            son_sz[u]+=son_sz[v];
        }
    }
    int query(int st,int limit){
        for (int p = 19; p >= 0; p--)
        {
            if (ver[st][p] > 0 && val[ver[st][p]] >= limit)
            {
                st = ver[st][p]; // 尝试成功，更新节点，下一次循环自动递减 p 继续检查
            }
        }
        return son_sz[st];
    }
};
void solved(){
    int n,m,q;
    cin>>n>>m>>q;
    vector<Edge>edge(m+1);
    for(int i=1;i<=m;i++){
        cin>>edge[i].u>>edge[i].v>>edge[i].w;
        edge[i].i=i;
    }
    KruskalTree kt(n);

    kt.build(edge);

    int type,x,y,limit=0;
    while(q--){
        cin>>type;
        if(type==1){
            for(int i=1;i<=cnt_pend;i++){
                kt.val[edge_to_tree[pend_edge[i]]]=pend_val[i];
            }
            cnt_pend=0;
            cin>>limit;
        }else if(type==2){
            cin>>x;
            cout<<kt.query(x,limit)<<endl;
        }else if(type==3){
            cin>>x>>y;//把第x条边的权值改为y
            if(edge_to_tree[x]!=0){
                pend_edge[++cnt_pend]=x;
                pend_val[cnt_pend]=y;
            }
        }
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
