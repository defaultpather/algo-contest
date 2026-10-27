#include<bits/stdc++.h>
using namespace std;

#define int long long
void solved(){
    int n,k;
    cin>>n>>k;
    vector<int>uni(n+1);
    for(int i=1;i<=2*k;i++){
        int x;
        cin>>x;
        uni[x]=1;
    }
    vector<vector<int>>adj(n+1);
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int ans=0;
    auto dfs=[&](auto&& self,int u,int fa)->int{
        int sz=uni[u];
        for(auto v:adj[u]){
            if(v!=fa){
                int c=self(self,v,u);
                sz+=c;
                ans+=min(c,2*k-c);
            }
        }
        return sz;
    };
    dfs(dfs,1,0);
    cout<<ans<<endl;
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