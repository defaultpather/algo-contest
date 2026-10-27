#include<bits/stdc++.h>
using namespace std;

#define int long long

const int N=6e5+10;
int n,m,mx;
int f[N][22];
int a[N];
void solved(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int l,r;
        cin>>l>>r;
        a[l]=max(a[l],r);
        mx=max(mx,r);
    }
    for(int i=1;i<=mx;i++){
        a[i]=max(a[i],a[i-1]);
    }
    for(int i=0;i<=mx;i++){
        f[i][0]=a[i];
    }
    for(int i=1;i<=20;i++){
        for(int j=0;j<=mx;j++){
            f[j][i]=f[f[j][i-1]][i-1];
        }
    }
    while(m--){
        int l,r;
        cin>>l>>r;
        int ans=0;
        for(int i=20;i>=0;i--){
            if(r>f[l][i]){
                ans+=1<<i;
                l=f[l][i];
            }
        }
        if(a[l]>=r){
            cout<<ans+1<<"\n";
        }else{
            cout<<"-1\n";
        }
    }
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