#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

#define endl '\n'
#define int long long
void solved()
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    s = " " + s;
    int ans = 0;
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        cnt += s[i] - '0';
        if (i % k == 0)
        {
            if (cnt == k)
            {
                ans++;
            }
            cnt = 0;
        }
    }
    cout << ans << endl;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--)
    {
        solved();
    }
    return 0;
}
