#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
const int N=2e5+10;

int p[N+1];
void solved(){
    int n,m;
    cin>>n>>m;
    vector<int>a(64);
    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        a[x]++;
    }
    for(int j=0;j<6;j++)
        for(int i=0;i<64;i++)
            if(!(i>>j&1))
                a[i]+=a[i^(1<<j)];
    vector<int>dp(64);
    for(int i=0;i<64;i++)dp[i]=p[a[i]];
    for(int j=0;j<6;j++)
        for(int i=0;i<64;i++)
            if(!(i>>j&1))
                dp[i]=(dp[i]-dp[i^(1<<j)]+mod)%mod;
    int ans=0;
    for(int i=0;i<64;i++){
        if(__builtin_popcountll(i)==m){
            ans=(ans+dp[i])%mod;
        }
    }
    if(m==6){
        ans=(ans-1+mod)%mod;
    }
    cout<<ans<<endl;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t=1;
    cin>>t;
    p[0]=1;
    for(int i=1;i<N;i++){
        p[i]=(p[i-1]<<1)%mod;
    }
    while(t--){
        solved();
    }
}