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
    for(int i=0;i<n-1;i++){
        int x,y;
        cin>>x>>y;
        x--,y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    vector<array<int,2>>dp(n,array<int,2>{1,1});
    auto dfs=[&](this auto&& dfs,int u,int fa)->array<int,2>{
        if(adj[u].size()==1&&adj[u][0]==fa){
            return {1,1};
        }
        for(auto v:adj[u]){
            if(v!=fa){
                auto [x,y]=dfs(v,u);
                (dp[u][0]*=x+y)%=mod;
                (dp[u][1]*=x)%=mod;
            }
        }
        return {dp[u][0],dp[u][1]};
    };
    auto ans=dfs(0,-1);
    cout<<(ans[0]+ans[1])%mod<<endl;
    return 0;
}
