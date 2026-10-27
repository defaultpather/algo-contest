#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

#define endl '\n'
#define int long long
const double eps=1e-6;
void solved(){
    int n;
    cin>>n;
    vector<int>x(n),t(n);
    for(int i=0;i<n;i++)cin>>x[i];
    for(int i=0;i<n;i++)cin>>t[i];
    double lo=*min_element(x.begin(),x.end());
    double hi=*max_element(x.begin(),x.end());
    auto check=[&](double m){
        double res=0;
        for(int i=0;i<n;i++){
            res=max(res,t[i]+abs(x[i]-m));
        }
        return res;
    };
    while(hi-lo>eps){
        double m1=lo+(hi-lo)/3.0;
        double m2=hi-(hi-lo)/3.0;
        if(check(m1)>check(m2)){
            lo=m1;
        }else{
            hi=m2;
        }
    }
    cout<<fixed<<setprecision(10)<<(lo+hi)/2.0<<"\n";
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t=1;
    cin>>t;
    while(t--){
        solved();
    }
    return 0;
}
