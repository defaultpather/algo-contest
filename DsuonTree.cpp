#include<bits/stdc++.h>
using namespace std;
struct TreeDsu{
    int n;
    vector<int>arr;
    vector<vector<int>>adj;
    vector<int>fa,dep,siz,son;
    vector<int>dfn,rev_dfn;
    int cntd;

    vector<int>colorCnt;
    vector<int>ans;
    int diff;

    TreeDsu(int n_,int max_val=1000010):n(n_),cntd(0),diff(0){
        arr.resize(n + 1);
        adj.resize(n + 1);
        fa.resize(n + 1);
        dep.resize(n + 1);
        siz.resize(n + 1);
        son.resize(n + 1);
        dfn.resize(n + 1);
        rev_dfn.resize(n + 1);
        colorCnt.assign(max_val + 1, 0);
        ans.resize(n + 1);
    }
    void addEdge(int u,int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs1(int u,int f){
        fa[u]=f;
        dep[u]=dep[f]+1;
        siz[u]=1;
        son[u]=0;
        dfn[u]=+cntd;
        rev_dfn[cntd]=u;
        for(auto v:adj[u]){
            if(v!=f){
                dfs1(v,u);
                siz[u]+=siz[v];
                if(son[u]==0||siz[v]>siz[son[u]]){
                    son[u]=v;
                }
            }
        }
    }
    void effect(int u){
        if(++colorCnt[arr[u]]==1){
            diff++;
        }
        for(auto v:adj[u]){
            if(v!=fa[u]){
                effect(v);
            }
        }
    }
    void cancel(int u){
        colorCnt[arr[u]]=0;
        for(auto v:adj[u]){
            if(v!=fa[u]){
                cancel(v);
            }
        }
    }
    void dfs2(int u,int keep){
        for(auto v:adj[u]){
            if(v!=fa[u]&&v!=son[u]){
                dfs2(v,0);
            }
        }
        if(son[u]!=0){
            dfs2(son[u],1);
        }
        if(++colorCnt[arr[u]]==1){
            diff++;
        }
        for(auto v:adj[u]){
            if(v!=fa[u]&&v!=son[u]){
                effect(v);
            }
        }
        ans[u]=diff;
        if(keep==0){
            diff=0;
            cancel(u);
        }
    }
    void work(int root=1){
        dfs1(root,0);
        dfs2(root,0);
    }
};
void solved(){
    int n;
    cin>>n;
    TreeDsu td(n);
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        td.addEdge(u,v);
    }
    for(int i=1;i<=n;i++){
        cin>>td.arr[i];
    }
    td.work(1);
    int m;
    cin>>m;
    for(int i=1,cur;i<=m;i++){
        cin>>cur;
        cout<<td.ans[cur]<<"\n";
    }
}
signed main(){
    solved();
}