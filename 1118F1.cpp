#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

#define endl '\n'
#define int long long

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
     
    int n;
    cin>>n;
    vector<int>color(n);
    int red=0,blue=0,w=0;
    for(int i=0;i<n;i++){
        cin>>color[i];
        if(color[i]==1){
            red++;
        }else if(color[i]==2){
            blue++;
        }else{
            w++;
        }
    }
    vector<vector<int>>adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<array<int,3>>f(n);
    int ans=0;
    auto dfs=[&](this auto&& dfs,int u,int fa)->void{
        f[u][color[u]]=1;
        for(auto v:adj[u]){
            if(v!=fa){
                dfs(v,u);
                for(int i=0;i<3;i++){
                    f[u][i]+=f[v][i];
                }
            }
        }
        if (f[u][1] == red&&f[u][2]==0)
            ans++;
        else if (f[u][2] == blue&&f[u][1]==0)
            ans++;
    };
    dfs(0,-1);
    cout<<ans<<endl;
    return 0;
}
