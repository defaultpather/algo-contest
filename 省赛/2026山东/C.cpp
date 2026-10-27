#include<bits/stdc++.h>
using namespace std;

#define int long long
const int INF=8e18;
void solved(){
    int n;
    cin>>n;
    vector<int>l(n),r(n);
    int lo=INF,hi=-INF;
    for(int i=0;i<n;i++){
        cin>>l[i]>>r[i];
        lo=min(l[i],lo);
        hi=max(hi,r[i]);
    }    
    auto check=[&](int x)->int{
        int res=0;
        for(int i=0;i<n;i++){
            if(l[i]>x)res+=(l[i]-x)*(l[i]-x);
            else if(r[i]<x)res+=(x-r[i])*(x-r[i]);
        }
        return res;
    };
    while(hi-lo>5){
        int m1=lo+(hi-lo)/3;
        int m2=hi-(hi-lo)/3;
        if(check(m1)<=check(m2)){
            hi=m2;
        }else{
            lo=m1;
        }
    }
    int ans=LLONG_MAX;
    for(int i=lo;i<=hi;i++){
        ans=min(ans,check(i));
    }
    cout<<ans<<'\n';
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