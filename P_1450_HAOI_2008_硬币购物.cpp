#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=100010;
int c[4],d[4];
int dp[N];
int n,s,cnt,ans;
signed main(){
    for(int i=0;i<4;i++){
        cin>>c[i];
    }
    cin>>n;
    dp[0]=1;
    for(int i=0;i<4;i++){
        for(int j=c[i];j<N;j++){
            dp[j]+=dp[j-c[i]];
        }
    }
    while(n--){
        for(int i=0;i<4;i++){
            cin>>d[i];
        }
        cin>>s;
        ans=0;
        for(int mask=0;mask<(1<<4);mask++){
            cnt=0;
            for(int i=0;i<4;i++){
                if(mask>>i&1){
                    cnt+=(d[i]+1)*c[i];
                }
            }
            if(s>=cnt){
                if(__popcount((unsigned long long)mask)&1){
                    ans-=dp[s-cnt];
                }else{
                    ans+=dp[s-cnt];
                }
            }
        }
        cout<<ans<<endl;
    }
}