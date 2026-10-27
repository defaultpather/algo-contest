#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

void solved(){
    double n, m, k;
    cin >> n >> m >> k;
    double ans = m * (k / 2 + ((n - 1) * k / (2 * (n + k))));
    cout << fixed << setprecision(18) << ans << endl;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T=1;
    // cin>>T;
    while(T--){
       solved();
    }
    return 0;
}
