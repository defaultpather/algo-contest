#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

#define endl '\n'
#define int long long

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1), b(n + 1);
    int mx = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    vector<int> d(n + 1);
    int pos = 0, neg = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
        d[i] = a[i] - k * b[i];
        if (d[i] >= 0)
            pos += d[i];
        else
            neg += d[i];
    }
    int offset = -neg;
    int tot = pos - neg;
    const int INF = 1e9;
    vector<int> dp(tot + 1, -INF);
    dp[offset] = 0;
    for (int i = 1; i <= n; i++)
    {
        if (d[i] >= 0)
        {
            for (int j = tot; j >= d[i]; j--)
            {
                if (dp[j - d[i]] != -INF)
                {
                    dp[j] = max(dp[j], dp[j - d[i]] + a[i]);
                }
            }
        }
        else
        {
            for (int j = 0; j <= tot + d[i]; j++)
            {
                if (dp[j - d[i]] != -INF)
                {
                    dp[j] = max(dp[j], dp[j - d[i]] + a[i]);
                }
            }
        }
    }
    if (dp[offset] == 0)
    {
        cout << "-1\n";
    }
    else
    {
        cout << dp[offset] << "\n";
    }
    return 0;
}
