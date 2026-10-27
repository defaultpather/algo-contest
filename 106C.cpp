#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

#define endl '\n'
#define int long long

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m,c,d;
    cin>>n>>m>>c>>d;
    vector<int>dp(n+1);
    for(int i=1;i<=n/c;i++){
        dp[i*c]=i*d;
    }
    for(int i=0;i<m;i++){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        for(int j=1;j<=a/b;j++){
            for(int k=n;k>=c;k--){
                dp[k]=max(dp[k],dp[k-c]+d);
            }
        }
    }
    int ans=0;
    for(int i=0;i<=n;i++){
        ans=max(ans,dp[i]);
    }
    cout<<ans<<"\n";
    return 0;
}
