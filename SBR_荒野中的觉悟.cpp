#include<bits/stdc++.h>
using namespace std;

#define int long long

const int mod=998244353;
int ksm(int a,int x){
    int res=1;
    while(x){
        if(x&1){
            res=res*a%mod;
        }
        a=a*a%mod;
        x>>=1;
    }
    return res%mod;
}
int inv(int x){
    return ksm(x,mod-2);
}
void solved(){
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    vector<int>p(n);
    int inv1=inv(n-1)*inv(100)%mod;
    int c0=0,P=1;
    for(int i=0;i<n;i++){
        p[i]=(1-a[i]*inv1%mod+mod)%mod;
        if(p[i]){
            P=P*p[i]%mod;
        }else{
            c0++;
        }
    }
    int ans=0;
    for(int i=0;i<n;i++){
        if(!p[i]){
            if(c0<=1){
                ans=(ans+P)%mod;
            }
        }else{
            int tmp=P*inv(p[i])%mod;
            if(c0>0){
                tmp=0;
            }
            ans=(ans+tmp)%mod;
        }
    }
    cout<<ans%mod<<'\n';
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