#include<bits/stdc++.h>
using namespace std;

#define int long long

void solved(){
    int n;
    cin>>n;
    vector<vector<int>>adj(n+1);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<array<int,3>>dp(n+1);
    auto dfs=[&](this auto&& dfs,int u,int fa)->void{
        if(adj[u].size()==1&&adj[u][0]==fa){
            dp[u]={0,1,0};
            return;
        }
        dp[u]={1,0,0};
        for(auto v:adj[u]){
            if(v!=fa){
                dfs(v,u);
                array<int,3>new_cur={0,0,0};
                for(int i=0;i<3;i++){
                    for(int j=0;j<3;j++){
                        new_cur[(i+j)%3]|=(dp[u][i]&&dp[v][j]);
                    }
                }
                dp[u]=new_cur;
            }
        }
        dp[u][1]=1;
    };
    dfs(1,0);
    cout<<(dp[1][0]?"YES\n":"NO\n");
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