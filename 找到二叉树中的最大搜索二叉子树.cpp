#include<bits/stdc++.h>
using namespace std;

#define int long long
const int INF=1e18;
int n,root;
struct node{
    int val;
    int ls;
    int rs;
};
struct Info{
    int mx,mn;
    bool isBst;
    int mxBstSize;
};
const int N = 1000010 ;
node arr[N];
Info f(int x){
    if(x==0){
        return Info{-INF,INF,1,0};
    }
    Info L=f(arr[x].ls);//后序遍历
    Info R=f(arr[x].rs);
    int mx=max(arr[x].val,max(L.mx,R.mx));
    int mn=min(arr[x].val,min(L.mn,R.mn));
    bool xisBst=L.isBst&&R.isBst&&arr[x].val>L.mx&&arr[x].val<R.mn;
    int mxSize=0;
    if(xisBst){
        mxSize=L.mxBstSize+R.mxBstSize+1;
    }else{
        mxSize=max(L.mxBstSize,R.mxBstSize);
    }
    return Info{mx,mn,xisBst,mxSize};
}
void solved(){
    cin>>n>>root;
    for(int i=1;i<=n;i++){
        int fa,l,r;
        cin>>fa>>l>>r;
        arr[fa].val=fa;
        arr[fa].ls=l;
        arr[fa].rs=r;
    }   
    cout<<f(root).mxBstSize<<endl;
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