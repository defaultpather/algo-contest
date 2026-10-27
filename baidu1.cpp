#include <bits/stdc++.h>

using namespace std;
#define int long long
#define debug(x) (cout<<"@ "<<#x<<" = "<<x<<endl)

void solved()
{
    int n, s;
    cin >> n >> s;
    vector<int> p(n);
    for(int i=0;i<n;i++){
        cin>>p[i];
    }
    int ans=s;
    for(int i=0;i<n;i++){
        if(p[i]>ans){
            ans=(ans+p[i]+1)/2;
        }
    }
    cout<<ans<<endl;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    cin >> t;
    while (t--)
    {
        solved();
    }
    return 0;
}