#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

#define endl '\n'
#define int long long

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n,k;
    cin>>n>>k;
    vector<int>a(n+1);
    int mx=0,mn=1e9;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        mx=max(a[i],mx);
    }
    sort(a.begin(),a.end());
    auto check=[&](int x){
        int mid=(n+1)/2;
        int tot=0;
        for(int i=mid;i<=n;i++){
            tot+=max(0ll,x-a[i]);
        }
        return tot<=k;
    };
    int lo=a[(n+1)/2],hi=mx+k+1;
    while(lo+1<hi){
        int mid=(lo+hi)/2;
        if(check(mid)){
            lo=mid;
        }else{
            hi=mid;
        }
    }
    cout<<lo<<"\n";
    return 0;
}
