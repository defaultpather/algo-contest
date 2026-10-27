#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

#define endl '\n'
#define int long long

const int INF=1e9;

void solved()
{
    int n;
    cin>>n;
    vector<vector<int>>adj(n);
    for(int i=1;i<n;i++){
        int x;
        cin>>x;
        x--;
        adj[x].push_back(i);
    }
    string s;
    cin>>s;
    vector<array<int,3>>dp(n);
    auto dfs=[&](this auto&& dfs,int u)->void{
        dp[u].fill(INF);
        dp[u][s[u]=='P'?1:(s[u]=='S'?2:0)]=0;
        for(auto v:adj[u]){
            dfs(v);
            array<int,3>g;
            g.fill(INF);
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    if((i|j)!=3){
                        g[i|j]=min(g[i|j],dp[u][i]+dp[v][j]);    
                    }
                    g[i]=min(g[i],dp[u][i]+dp[v][j]+1);
                }
            }
            dp[u]=g;
        }
    };
    dfs(0);
    cout<<min({dp[0][0],dp[0][1],dp[0][2]})<<"\n";
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t=1;
    cin>>t;
    while(t--){
        solved();
    }
    return 0;
}
