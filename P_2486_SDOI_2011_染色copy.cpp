#include<bits/stdc++.h>
using namespace std;

const int MAXN=100010;
int n,m;
int arr[MAXN];

int head[MAXN],nxt[MAXN<<1],to[MAXN<<1];
int cntg;

int fa[MAXN],dep[MAXN],siz[MAXN],son[MAXN],top[MAXN],dfn[MAXN],rev_dfn[MAXN];
int cntd;

int sum[MAXN<<2],lcolor[MAXN<<2],rcolor[MAXN<<2],change[MAXN<<2];

void addEdge(int u,int v){
        nxt[++cntg]=head[u];
        to[cntg]=v;
        head[u]=cntg;
}

void dfs1(int u,int f){
    fa[u]=f;
    dep[u]=dep[f]+1;
    siz[u]=1;
    for(int e=head[u],v;e>0;e=nxt[e]){
        v=to[e];
        if(v!=f){
            dfs1(v,u);
            fa[v]=u;
            siz[u]+=siz[v];
            if(siz[v]>siz[son[u]]){
                son[u]=v;
            }
        }
    }
}
void dfs2(int u,int t){
    top[u]=t;
    dfn[u]=++cntd;
    rev_dfn[cntd]=u;
    if(son[u]==0)return;
    dfs2(son[u],t);
    for(int e=head[u],v;e>0;e=nxt[e]){
        v=to[e];
        if(v!=fa[u]&&v!=son[u]){
            dfs2(v,v);
        }
    }
}
void up(int i){
    sum[i]=sum[i<<1]+sum[i<<1|1];
    if(rcolor[i<<1]==lcolor[i<<1|1]){
        sum[i]--;
    }
    lcolor[i]=lcolor[i<<1];
    rcolor[i]=rcolor[i<<1|1];
}
void build(int l,int r,int i)
{
    if(l==r){
        sum[i]=1;
        lcolor[i]=arr[rev_dfn[l]];
        rcolor[i]=arr[rev_dfn[l]];
    }else{
        int mid=l+r>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}
void lazy(int i,int v){
    sum[i]=1;
    lcolor[i]=v;
    rcolor[i]=v;
    change[i]=v;
}
void down(int i){
    if(change[i]!=0){//其实直接相当于在node上的那个tagbool值判断了
        lazy(i<<1,change[i]);//分别传给左右儿子
        lazy(i<<1|1,change[i]);
        change[i]=0;//标记清空
    }
}
void update(int jobl,int jobr,int jobv,int l,int r,int i=1){
    if(jobl<=l&&jobr>=r){
        lazy(i,jobv);
    }else{
        down(i);
        int mid=l+r>>1;
        if(jobl<=mid){
            update(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            update(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}
//树剖路径修改:将从x到y的路径上的所有结点改为v
void pathUpdate(int x,int y,int v){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])swap(x,y);
        update(dfn[top[x]],dfn[x],v,1,n);
        x=fa[top[x]];
    }
    if(dfn[x]>dfn[y])swap(x,y);
    update(dfn[x],dfn[y],v,1,n);
}
int query(int jobl,int jobr,int l,int r,int i=1){
    if(jobl<=l&&r<=jobr){
        return sum[i];
    }
    down(i);
    int mid=l+r>>1;
    if(jobr<=mid){
        return query(jobl,jobr,l,mid,i<<1);
    }else if(jobl>mid){
        return query(jobl,jobr,mid+1,r,i<<1|1);
    }else{
        int ans=query(jobl,jobr,l,mid,i<<1)+query(jobl,jobr,mid+1,r,i<<1|1);
        if(rcolor[i<<1]==lcolor[i<<1|1])ans--;
        return ans;
    }
}
int point_query(int jobi,int l,int r,int i=1){
    if(l==r)return lcolor[i];
    down(i);//确保拿到的颜色是最新的
    int mid=l+r>>1;
    if(jobi<=mid)return point_query(jobi,l,mid,i<<1);
    else return point_query(jobi,mid+1,r,i<<1|1);
}
int pathColors(int x,int y){
    int ans=0,sonc,fac;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])swap(x,y);
        ans+=query(dfn[top[x]],dfn[x],1,n);
        sonc=point_query(dfn[top[x]],1,n);
        fac=point_query(dfn[fa[top[x]]],1,n);
        if(sonc==fac)ans--;
        x=fa[top[x]];
    }
    if(dfn[x]>dfn[y])swap(x,y);
    return ans+query(dfn[x],dfn[y],1,n);
}
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addEdge(u,v);
        addEdge(v,u);
    }
    dfs1(1,0);
    dfs2(1,1);
    build(1,n,1);
    string op;
    int x,y;
    while(m--){
        cin>>op;
        cin>>x>>y;
        if(op=="C"){
            int z;
            cin>>z;
            pathUpdate(x,y,z);
        }else{
            cout<<pathColors(x,y)<<"\n";
        }
    }
}