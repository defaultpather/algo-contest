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
    vector<vector<int>>adj(n+1);
    vector<int>val(n+1);
    int root,sum=0;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x>>val[i];
        sum+=val[i];
        if(x){
            adj[x].push_back(i);
        }else{
            root=i;
        }
    }
    if(sum%3){
        cout<<"-1\n";
        exit(0);
    }
    int lst=0;
    auto dfs=[&](auto&& self,int u)->void{
        for(auto v:adj[u]){
            self(self,v);
            val[u]+=val[v];
        }
        if(u!=root&&val[u]==sum/3){//如果sum为0的话,根节点没有父边不能作为输出
            if(lst){
                cout<<lst<<" "<<u<<"\n";
                exit(0);
            }
            lst=u;
            val[u]=0;
        }
    };
    dfs(dfs,root);
    cout<<"-1\n";
    return 0;
}
