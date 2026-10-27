#include<bits/stdc++.h>
using namespace std;

#define int long long

const int N=1005;

int fa[1<<12][N];
int find(int mask,int u){
    return u == fa[mask][u] ? u : fa[mask][u] = find(mask,fa[mask][u]);
}
void add(int u,int v,int w){
    if(find(w,u)==find(w,v))return;
    fa[w][find(w,u)]=find(w,v);
    for(int i=0;i<12;i++){
        if((w>>i)&1){
            add(u,v,w^(1<<i));
        }
    }
}
int query(int u,int v){
    if(find(0,u)!=find(0,v))return -1;
    int res=0;
    for(int i=11;~i;i--){
        int cand=res|(1<<i);
        if(find(cand,u)==find(cand,v)){
            res=cand;
        }
    }
    return res;
}
void solved(){
    int n,q;
    cin>>n>>q;
    for(int i=0;i<(1<<12);i++){
        iota(fa[i]+1,fa[i]+1+n,1);
    }
    int res=0;
    while(q--){
        char ch;
        while((ch=getchar())!='+'&&ch!='?');
        if(ch=='+'){
            int u,v,w;
            cin>>u>>v>>w;
            add(u,v,w);
        }else{
            int u,v;
            cin>>u>>v;
            res+=query(u,v);
        }
    }
    cout<<res<<"\n";
}
signed main(){
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    int T=1;
    cin>>T;
    while(T--){
        solved();
    }
}