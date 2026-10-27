#include<bits/stdc++.h>
using namespace std;

#define int long long
void solved(){
    int n,m;
    cin>>n>>m;
    vector<tuple<double,double,int>>a(n);
    for(int i=0;i<n;i++){
        int p,v,w;
        cin>>p>>v>>w;
        a[i]=make_tuple(v,p,w);
    }
    sort(a.begin(),a.end());
    vector<double>dp(m+1,0.0);
    for(int i=0;i<n;i++){
        auto [v,p,w]=a[i];
        for(int j=m;j>=w;j--){
            dp[j]=max(dp[j],dp[j-w]*(1-p/100)+p/100.0*v);
        }
    }
    cout<<fixed<<setprecision(12)<<dp[m]<<"\n";
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t=1;
    cin>>t;
    while(t--){
        solved();
    }
}