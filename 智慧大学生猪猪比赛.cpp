#include<bits/stdc++.h>
using namespace std;

#define int long long

const int INF=1e18;

void solved(){
    int n,d;
    cin>>n>>d;
    vector<int>a(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a.begin(),a.end());
    vector<int>dp(n+1,-INF);
    dp[0]=0;
    // dp[1]=a[n];
    for(int i=2;i<=n;i++){
        if(a[i]-a[i-1]<=2*d){
            dp[i]=max(dp[i],dp[i-2]+(a[i-1]+d)*2);
        }
        if(i>2&&a[i]-a[i-2]<=2*d){
            dp[i]=max(dp[i],dp[i-3]+(a[i-2]+d)*3);
        }
    }
    if(dp[n]<0){
        cout<<"Impossible\n";
    }else{
        cout<<dp[n]<<"\n";
    }
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