#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N=2e5+10;
int tree[4*N],lazy[4*N];
void build(int node,int l,int r,vector<int>&val){
    lazy[node]=0;
    if(l==r){
        tree[node]=val[l];
        return;
    }
    int mid=l+r>>1;
    build(node<<1,l,mid,val);
    build(node<<1|1,mid+1,r,val);
    tree[node]=min(tree[node<<1],tree[node<<1|1]);
}
void apply(int node,int val){
    tree[node]+=val;
    lazy[node]+=val;
}
void push_down(int node){
    if(lazy[node]){
        apply(node<<1,lazy[node]);
        apply(node<<1|1,lazy[node]);
        lazy[node]=0;
    }
}
void update(int node,int l,int r,int pl,int pr,int val){
    if(pr<l||pl>r)return;
    if(pl<=l&&r<=pr){
        apply(node,val);
        return;
    }
    push_down(node);
    int mid=l+r>>1;
    update(node<<1,l,mid,pl,pr,val);
    update(node<<1|1,mid+1,r,pl,pr,val);
    tree[node]=min(tree[node<<1],tree[node<<1|1]);
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin>>n;
    vector<int>p(n+1),pos(n+1);
    for(int i=1;i<=n;i++){
        cin>>p[i];
        pos[p[i]]=i;
    }
    vector<int>b(n+1),a(n+1);
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++){
        b[i]=a[pos[i]];
    }
    vector<int>g(n+1);
    for(int i=1;i<=n;i++){
        g[i]=g[i-1]+b[i];
    }
    build(1,0,n,g);
    int ans=LLONG_MAX;
    for(int k=1;k<n;k++){
        int x=p[k];
        int c=a[k];
        update(1,0,n,0,x-1,c);
        update(1,0,n,x,n,-c);
        ans=min(ans,tree[1]);
    }
    cout<<ans<<'\n';
}
