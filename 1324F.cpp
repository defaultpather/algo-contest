#include<bits/stdc++.h>
using namespace std;

#define int long long

void solved(){
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
        if(a[i])a[i]=1;
        else a[i]=-1;
    }
    vector<vector<int>>adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int>dp(n);
    auto dfs1=[&](this auto&& dfs,int u,int fa)->void{
        dp[u]=a[u];
        for(auto v:adj[u]){
            if(v!=fa){
                dfs(v,u);
                dp[u]+=max(dp[v],0ll);
            }
        }
    };
    vector<int>ans(n);
    auto dfs2=[&](this auto&& dfs2,int u,int fa)->void{
        for(auto v:adj[u]){
            if(v!=fa){
                int parent=ans[u]-max(0ll,dp[v]);
                ans[v]=dp[v]+max(0ll,parent);
                dfs2(v,u);
            }
        }
    };
    dfs1(0,-1);
    ans[0]=dp[0];
    dfs2(0,-1);
    for(int i=0;i<n;i++){
        cout<<ans[i]<<" \n"[i==n-1];
    }
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