#include<bits/stdc++.h>
using namespace std;

#define int long long

void solved(){
    int n;
    cin>>n;
    vector<vector<int>>adj(n+1);
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int>val(n+1);
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    vector<int>f(n+1),g(n+1);
    auto dfs=[&](this auto self,int u,int fa)->void{
        for(auto v:adj[u]){
            if(v!=fa){
                self(v,u);
                f[u]=max(f[u],f[v]);
                g[u]=max(g[u],g[v]);
            }
        }
        int k=val[u]+f[u]-g[u];
        if(k>0){
            g[u]+=k;
        }else{
            f[u]+=-k;
        }
    };
    dfs(1,0);
    cout<<f[1]+g[1]<<endl;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T=1;
    // cin>>T;
    while(T--){
        solved();
    }
}