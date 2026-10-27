#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int N=10;
const int MAX_BIT=1<<N;

int n,k;
vector<int>state;
vector<vector<vector<int>>>dp(N,vector<vector<int>>(MAX_BIT,vector<int>(90,0)));
int cnt[MAX_BIT];
void solved(){
    cin>>n>>k;
    for(int mask=0;mask<(1<<n);mask++){
        if((mask&mask<<1)==0){
            state.push_back(mask);
            cnt[mask]=__popcount((unsigned)mask);
        }
    }    
    dp[0][0][0]=1;
    for(int i=1;i<=n;i++){
        for(auto cur:state){
            int c1=cnt[cur];
            for(auto lst:state){
                if(((cur&lst)==0)&&(cur>>1&lst)==0&&(cur<<1&lst)==0){
                    for (int j = c1; j <= k; ++j){ 
                        dp[i][cur][j] += dp[i - 1][lst][j-c1];
                    }
                }
            }
        }
    }
    int  ans=0;
    for(auto s:state){
        ans+=dp[n][s][k];
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
