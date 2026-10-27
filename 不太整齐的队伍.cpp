#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
#define int long long

void solved()
{
    int n,k;
    cin >>n>>k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    if (k >= n){
        cout << n << '\n';
        return;
    }
    vector<int> lst(k + 1),mx(k+1);
    for (int i = 1;i<=n;i++){
        int x = a[i];
        if (x <= k){
            mx[x] = max(mx[x], i - lst[x] - 1);
            lst[x] = i;
        }
    }
    int ans = 0;
    for (int x = 0; x <= k; x++)
    {
        mx[x] = max(mx[x], n - lst[x]);
        ans = max(ans, mx[x]);
    }
    cout << ans << "\n";
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--){
        solved();
    }
    return 0;
}
