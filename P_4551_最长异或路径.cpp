#include<bits/stdc++.h>
using namespace std;
const int N=100010;
const int BN=N*31+10;
struct Edges{
    int to,w,next;
}edge[N*2];
int head[N];
int edge_cnt=0;

void addEdge(int u,int v,int w){
    edge[++edge_cnt]={v,w,head[u]};
    head[u]=edge_cnt;//头插法
}
int D[N];
void dfs(int u,int fa,int xor_sum){
    D[u]=xor_sum;
    for(int e=head[u];e!=0;e=edge[e].next){//u的所有邻居边号
        int v=edge[e].to;
        int w=edge[e].w;
        if(v!=fa)
        dfs(v,u,xor_sum^w);
    }
}
int tree[BN][2];
int tree_cnt=1;
void insert(int x){
    int cur=1;
    for(int i=30;i>=0;i--){
        int path=x>>i&1;
        if(tree[cur][path]==0){
            tree[cur][path]=++tree_cnt;
        }
        cur=tree[cur][path];
    }
}
int query(int x){
    int cur=1;
    int res=0;
    for(int i=30;i>=0;i--){
        int path=x>>i&1;
        int best_path=path^1;
        if(tree[cur][best_path]!=0){
            res|=(1<<i);
            cur=tree[cur][best_path];
        }else{
            cur=tree[cur][path];
        }
    }
    return res;
}
signed main(){
    int n;
    cin>>n;

    for(int i=0;i<n-1;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    dfs(1,0,0);

    for(int i=1;i<=n;i++){
        insert(D[i]);
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        ans=max(ans,query(D[i]));
    }
    cout<<ans<<"\n";
}