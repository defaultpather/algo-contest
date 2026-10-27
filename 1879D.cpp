#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
#define int long long
const int mod=998244353;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin>>n;
    vector<int>a(n+1);
    vector<int>p(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        p[i]=p[i-1]^a[i];
    }
    int ans=0;
    for(int bit=0;bit<=30;bit++){
        array<int,2>cnt{},sum{};
        int res=0;
        for(int j=0;j<=n;j++){
            int v=((p[j]>>bit)&1);
            int o=(v^1);
            res+=j*cnt[o]-sum[o];
            cnt[v]++;
            sum[v]+=j;
        }
        int pw=(1<<bit)%mod;
        ans=(ans%mod+res%mod*pw%mod)%mod;
    }
    cout<<ans<<"\n";

    return 0;
}
