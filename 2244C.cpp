#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

#define endl '\n'
#define int long long
void solved(){
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) cin >> p[i];

    int g = gcd(x, y);
    for (int i = 1; i <= n; i++) {
        if ((i - p[i]) % g != 0) {  
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
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
