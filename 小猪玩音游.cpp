#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;

    vector<double> d(n);
    for (int i = 0; i < n; i++)
    {
        cin >> d[i];
    }
    vector<double> best(n);
    for (int i = 0; i < m; i++)
    {
        int s;
        double a;
        cin >> s >> a;
        s--;
        double sc = 0.0;
        if (a >= 97.50)
        {
            sc = d[s] + 2.15 * (a - 97.50) / 3.40;
        }
        best[s] = max(best[s], sc);
    }
    sort(best.begin(), best.end(), greater<double>());
    double ans = 0.0;
    for (int i = 0; i < min(30, n); i++)
    {
        ans += best[i];
    }
    ans /= 30.0;
    cout << fixed << setprecision(10) << ans << '\n';
    return 0;
}
