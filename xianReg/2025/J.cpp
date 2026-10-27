#include<bits/stdc++.h>
using namespace std;

#define int long long
const int INF=1e9;
void solved(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>>adj(n+1);
    vector<int>c(n+1);
    for(int i=1;i<=n;i++){
        cin>>c[i];
    }     
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    auto dfs1=[&](this auto&& dfs1,int u,int fa)->void{
        int mn1=INF,mn2=INF;
        for(auto v:adj[u]){
            if(v!=fa){
                dfs1(v,u);
                if(c[v]<mn1){
                    mn2=mn1;
                    mn1=c[v];
                }else if(c[v]<mn2){
                    mn2=c[v];
                }
            }
        }
        c[u]=min(c[u],mn1+mn2);
    };
    vector<int>val(n+1);
    vector<int>dfn(n+1);
    int timer=0;
    vector<int>lst(n+1);
    auto dfs2=[&](this auto&& dfs2,int u,int fa)->void{
        dfn[u]=++timer;
        int mn1=INF,mn2=INF;
        for(auto v:adj[u]){
            if(v!=fa){
                if(c[v]<mn1){
                    mn2=mn1;
                    mn1=c[v];
                }else if(c[v]<mn2){
                    mn2=c[v];
                }
            }
        }
        for(auto v:adj[u]){
            if(v!=fa){
                val[v]=val[u]+(c[v]==mn1?mn2:mn1);
                dfs2(v,u);
            }
        }
        lst[u]=timer;
    };
    dfs1(1,0);
    dfs2(1,0);
    while(m--){
        int x,y;
        cin>>x>>y;
        if(!(dfn[y]<=dfn[x]&&dfn[x]<=lst[y])){
            cout<<"-1\n";
            continue;
        }
        cout<<val[x]-val[y]<<"\n";
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T=1;
    cin>>T;
    while(T--){
        solved();
    }
}