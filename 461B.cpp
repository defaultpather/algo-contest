#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

#define endl '\n'
#define int long long

const int mod=1e9+7;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin>>n;
    vector<vector<int>>adj(n);
    for(int i=1;i<n;i++){
        int a;
        cin>>a;
        adj[a].push_back(i);
        adj[i].push_back(a);
    }
    vector<int>c(n);
    for(int i=0;i<n;i++){
        cin>>c[i];
    }
    vector<array<int,2>>dp(n,array<int,2>{0,0});
    auto dfs=[&](this auto&& dfs,int u,int fa)->void{
        dp[u][c[u]]=1;
        for(auto v:adj[u]){
            if(v==fa)continue;
            dfs(v,u);
            dp[u][1]=(dp[u][1]*dp[v][0]%mod+dp[u][1]*dp[v][1]%mod+dp[u][0]*dp[v][1]%mod)%mod;
            dp[u][0]=(dp[u][0]*dp[v][0]%mod+dp[u][0]*dp[v][1]%mod)%mod;
        }
    };
    dfs(0,-1);
    cout<<dp[0][1]<<"\n";
    return 0;
}
