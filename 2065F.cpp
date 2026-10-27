#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long
const int MAXN=5e5+10;
int dfn[MAXN], sz[MAXN], timer = 0;

void get_dfn(int u, int fa,auto adj)
{
    dfn[u] = ++timer; // 首次进入节点时记录时间戳
    sz[u] = 1;
    for (int v : adj[u])
    {
        if (v == fa)
            continue;
        get_dfn(v, u);
        sz[u] += sz[v];
    }
}
void solved(){
    int n;
    cin>>n;
    vector<vector<int>>g(n+1);
    vector<int>a(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    get_dfn(1,0,g);
    vector<vector<int>>ans(n+1);
    for(int i=1;i<=n;i++){
        
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T=1;
    cin>>T;
    while(T--){
       solved();
    }
    return 0;
}
