#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e18;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    long long l;
    cin>>n>>l>>k;
    vector<long long> d(n + 2);

    vector<long long> a(n + 2);
    for (int i = 1; i <= n; ++i)
    {
        cin >> d[i];
    }
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
    }
    d[n + 1] = l;
    a[n + 1] = 0;
    vector<vector<long long>> dp(n + 3, vector<long long>(k + 1, INF));
    dp[1][0] = 0;

    for (int i = 2; i <= n + 1; ++i)
    {
        for (int j = 0; j <= k; ++j)
        {
            // 枚举上一个被保留的牌 p
            for (int p = 1; p < i; ++p)
            {
                int removed = i - p - 1; // p 和 i 之间拆除的牌数
                if (j >= removed)
                {
                    dp[i][j] = min(dp[i][j], dp[p][j - removed] + (d[i] - d[p]) * a[p]);
                }
            }
        }
    }
    long long ans = INF;
    for (int j = 0; j <= k; ++j)
    {
        ans = min(ans, dp[n + 1][j]);
    }

    cout << ans << "\n";

    return 0;
}