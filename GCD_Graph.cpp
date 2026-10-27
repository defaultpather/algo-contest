#include<bits/stdc++.h>
using namespace std;
const int N=1e7+10;
const int inf=1e9;
signed main(){
    vector<int>pr(N);
    iota(pr.begin(),pr.end(),0);
    for(int i=2;i<N;i++){
        if(pr[i]==i){
            for(int j=i;j<N;j+=i){
                pr[j]=i;
            }
        }
    }    
    auto HZ=[&](int target,int R){
        int tmp=target;
        vector<int>fac;
        while(tmp>1){
            int cur=pr[tmp];
            while(tmp%cur==0){
                tmp/=cur;
            }
            fac.emplace_back(cur);
        }
        //二进制状压枚举每种质因数组合
        int k=fac.size();//多少个不同的质因子
        int ans=0;
        for(int i=0;i<(1<<k);i++){
            int cur=R;
            for(int j=0;j<k;j++){
                if(i>>j&1){
                    cur/=fac[j];
                }
            }
            if(__popcount(i)&1)ans-=cur;
            else ans+=cur;
        }
        return ans;
    };
    auto calc=[&](int target,int R){
        int mx_prime=target-1;
        while(pr[mx_prime]!=mx_prime)mx_prime--;
        if(mx_prime>R){
            return 2*R-HZ(target,R);
        }
        int ans=2*(mx_prime-1)-HZ(target,mx_prime-1);
        int gap=target-mx_prime;
        vector<int>dp(gap+1,inf);//dp[i]表示从target-i到n的最短距离
        dp[0]=0;
        for(int i=0;i<=gap;i++){
            for(int j=0;j<i;j++){
                dp[i]=min(dp[i],dp[j]+__gcd(target-i,target-j));
            }
            if(target-i<=R)ans+=dp[i];
        }
        return ans;
    };
    int t;
    cin>>t;
    while(t--){
        int l,r,n;
        cin>>l>>r>>n;
        cout<<calc(n,r)-calc(n,l-1)<<endl;
    }
}