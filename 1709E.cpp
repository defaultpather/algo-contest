#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
const int N=200010;
int a[N];
int d[N];
set<int>s[N];
vector<int>adj[N];
int ans;
void dfs1(int u,int f){
    d[u]=d[f]^a[u];
    for(auto v:adj[u]){
        if(v!=f){
            dfs1(v,u);
        }
    }
}
void dfs2(int u,int f){
    s[u].insert(d[u]);
    bool ok=0;
    for(auto v:adj[u]){
        if(v==f)continue;
        dfs2(v,u);
        if(s[u].size()<s[v].size())swap(s[u],s[v]);
        for(auto x:s[v]){
            if(s[u].count(x^a[u])){
                ok=1;
            }
        }
        
        for(auto x:s[v]){
            s[u].insert(x);
        }
        s[v].clear();
    }
    if(ok){
        ans++;
        s[u].clear();
    }
}
void solved(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,0);
    cout<<ans<<"\n";
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(0);
    int T=1;
    // cin>>T;
    while(T--){
       solved();
    }
    return 0;
}
