#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int mod=1e8;

int field[13];
vector<int>state;
vector<vector<int>>dp(13,vector<int>(1<<12));

void solved(){
    int n,m;
    cin>>m>>n;
    for(int i=1;i<=m;i++){
        int mask=0;
        for(int j=0;j<n;j++){
            int val;
            cin>>val;
            if(val==1){
                mask|=(1<<(n-1-j));
            }
        }
        field[i]=mask;
    }
    for(int i=0;i<(1<<n);i++){
        if((i&i<<1)==0){
            state.push_back(i);
        }
    }

    dp[0][0]=1;
    for(int i=1;i<=m;i++){
        for(auto s1:state){
            if((field[i]&s1)==s1){
                for(auto s2:state){
                    if((s2&s1)==0){
                        dp[i][s1]=(dp[i][s1]+dp[i-1][s2])%mod;
                    }
                }
            }
        }
    }
    int ans=0;
    for(int i=0;i<(1<<n);i++){
        (ans+=dp[m][i])%=mod;
    }
    cout<<ans<<endl;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T=1;
    // cin>>T;
    while(T--){
       solved();
    }
    return 0;
}
