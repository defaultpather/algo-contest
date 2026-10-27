#include <bits/stdc++.h>
using namespace std;

#define int long long

const int INF = 3e18;

void solved()
{
    
    int n,k;
    cin>>n>>k;
    vector<int>s(n+1),c(n+1);
    int mn=INF;
    for(int i=1;i<=n;i++){
        int a,b,cc;
        cin>>a>>b>>cc;
        s[i]=a+b+cc;
        mn=min(mn,s[i]);
        if(a>b||b>cc){
            c[i]=0;
        }else if(a==b&&b==cc){
            c[i]=INF;
        }else{
            c[i]=2ll*(min(b-a,cc-b)+1);
        }
    }
    auto check=[&](int S)->bool{
        int tot=0;
        for(int i=1;i<=n;i++){
            if(s[i]>=S)continue;
            if(c[i]>=INF)return false;
            tot+=c[i]+S-s[i];
            if(tot>k)return false;
        }  
        return tot<=k;
    };
    int lo=mn,hi=mn+k;
    while(lo<hi){
        int mid=lo+(hi-lo+1)/2;
        if(check(mid)){
            lo=mid;
        }else{
            hi=mid-1;
        }
    }
    cout<<hi<<"\n";
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
    {
        solved();
    }
}