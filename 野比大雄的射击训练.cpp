#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,k;
    cin>>n>>k;
    int ans = 0;
    for (int i = 0; i < k; i++)
    {
        int x, y;
        cin >> x >> y;

        int d = max(abs(x - n), abs(y - n));
        ans += n - d;
    }

    cout << ans << '\n';

    return 0;
}
