#include<bits/stdc++.h>
using namespace std;

#define int long long
const int INF=1e18;
const int N=2e5+10;
vector<int>fa(N);
int find(int u){
    return fa[u]==u?fa[u]:fa[u]=find(fa[u]);
}
bool merge(int u,int v){
    int fu=find(u);
    int fv=find(v);
    if(fu==fv)return false;
    fa[fu]=fv;
    return true;
}
void solve(){
    int n,m,k;
    cin>>n>>m>>k;
    vector<int>a(n);
    vector<bool>isSp(n);
    for(int i=0;i<k;i++){
        cin>>a[i];
        a[i]--;
        isSp[a[i]]=1;
    }
    vector<array<int,3>>adj;
    vector<int>best(n,INF);
    int mnP=INF;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        u--,v--;
        if(u==v)continue;
        else if(isSp[u]&&isSp[v]){
            if(n==2)mnP=min(mnP,w);
        }else if(isSp[u]){
            best[u]=min(best[u],w);
        }else if(isSp[v]){
            best[v]=min(best[v],w);
        }else{
            adj.push_back({u,v,w});
        }
    }
    //全特殊
    if(k==n){
        if(n==2)cout<<(mnP==INF?-1:mnP)<<'\n';
        else cout<<"-1\n";
        return;
    }
    int ans=0;
    //特殊点至少一个非特殊
    for(int i=0;i<k;i++){
        if(best[a[i]]==INF){
            cout<<"-1\n";
            return;
        }
        ans+=best[a[i]];
    }
    sort(adj.begin(),adj.end(),[&](const auto& x,const auto& y){
        return x[2]<y[2];
    });
    iota(fa.begin(),fa.end(),0);
    for(auto& e:adj){
        if(merge(e[0],e[1]))ans+=e[2];
    }
    //非特殊点必须连通
    int root=-1;
    for(int i=0;i<n;i++){
        if(isSp[i])continue;
        int r=find(i);
        if(root==-1)root=r;
        else if(r!=root){
            cout<<"-1\n";
            return;
        }
    }
    cout<<ans<<"\n";
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t=1;
    cin>>t;
    while(t--){
        solve();
    }
}