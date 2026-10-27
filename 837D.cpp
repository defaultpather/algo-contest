#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> c2(n), c5(n);
    int sum5 = 0; // 所有数 5 的总个数
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        while (x % 2 == 0)
        {
            c2[i]++;
            x /= 2;
        }
        while (x % 5 == 0)
        {
            c5[i]++;
            x /= 5;
        }
        sum5 += c5[i];
    }

    const int NEG = -1e18;
    // dp[j][s] = 恰好选 j 个数、5 的总个数为 s 时，能得到的最大 2 的个数
    vector<vector<int>> dp(k + 1, vector<int>(sum5 + 1, NEG));
    dp[0][0] = 0;
    for (int i = 0; i < n; i++)
    { 
        for (int j = k; j >= 1; j--)
        { 
            for (int s = sum5; s >= c5[i]; s--)
            {
                if (dp[j - 1][s - c5[i]] != NEG)
                    dp[j][s] = max(dp[j][s], dp[j - 1][s - c5[i]] + c2[i]);
            }
        }
    }

    int ans = 0;
    for (int s = 0; s <= sum5; s++)
    {
        if (dp[k][s] != NEG)
            ans = max(ans, min(s, dp[k][s])); 
    }
    cout << ans << "\n";
    return 0;
}