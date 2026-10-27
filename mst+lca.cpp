#include<bits/stdc++.h>
using namespace std;

const int INF=1e9;

struct Edge{
    int u,v,w;
    bool operator<(const Edge& x){
        return w>x.w;
    }
};
struct DSU{
    int n;
    vector<int>fa;
    DSU(int n){
        this->n=n;
        fa.resize(n+1);
        iota(fa.begin(),fa.end(),0);
    }
    int find(int u){
        return fa[u]==u?u:fa[u]=find(fa[u]);
    }
    bool merge(int u,int v){
        u=find(u);
        v=find(v);
        if(u!=v){
            fa[u]=v;
            return 1;
        }
        return 0;
    }
};
struct Tree{
    int n;
    struct treeEdge{
        int to,w;
    };
    vector<vector<treeEdge>>adj;
    vector<vector<int>>ver;
    vector<int>dep;
    vector<vector<int>>min_w;
    vector<bool>vis;
    DSU dsu;

    Tree(int n):n(n),dsu(n){
        adj.resize(n+1);
        dep.assign(n+1,0);
        ver.resize(n+1,vector<int>(22,0));
        min_w.resize(n+1,vector<int>(22,INF));
        vis.assign(n+1,false);
    }
    void addEdge(int u,int v,int w){
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    void dfs(int u,int fa,int w){
        vis[u]=true;
        dep[u]=dep[fa]+1;
        ver[u][0]=fa;
        min_w[u][0]=w;
        
        for(int i=1;i<=__lg(dep[u]);i++){//msb
            ver[u][i]=ver[ver[u][i-1]][i-1];
            min_w[u][i]=min(min_w[u][i-1],min_w[ver[u][i-1]][i-1]);
        }
        for(auto [to,w]:adj[u]){
            if(to==fa)continue;
            dfs(to,u,w);
        }        
    }
    int query_min(int x,int y){
        if(dsu.find(x)!=dsu.find(y))return -1;
        
        if(dep[x]<dep[y])swap(x,y);
        
        int ans=INF;
        while(dep[x]>dep[y]){
            int k=__lg(dep[x]-dep[y]);
            ans=min(ans,min_w[x][k]);
            x=ver[x][k];
        }
        
        if(x==y)return ans;
        
        for(int k=__lg(dep[x]);k>=0;k--){
            if(ver[x][k]!=ver[y][k]){
                ans=min({ans,min_w[x][k],min_w[y][k]});
                x=ver[x][k];
                y=ver[y][k];
            }
        }
        ans=min({ans,min_w[x][0],min_w[y][0]});
        return ans;
    }
    void work_forest(){
        for(int i=1;i<=n;i++){
            if(!vis[i]){
                dfs(i,0,INF);
            }
        }
    }
};

signed main(){
    int n,m;
    cin>>n>>m;
    vector<Edge>edges(m);
    for(int i=0;i<m;i++){
        cin>>edges[i].u>>edges[i].v>>edges[i].w;
    }  
    Tree tree(n);
    sort(edges.begin(),edges.end());
    for(auto [u,v,w]:edges){
        if(tree.dsu.merge(u,v)){
            tree.addEdge(u,v,w);
        }
    }
    tree.work_forest();
    int q;
    cin>>q;
    while(q--){
        int x,y;
        cin>>x>>y;
        cout<<tree.query_min(x,y)<<endl;
    }
}