#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

#define endl '\n'
#define int long long
void solved()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    vector<int> b(n + 1);
    iota(b.begin(), b.end(), 0);
    for (int i = 1; i <= n; i++)
    {
        b[i] = b[i - 1] + b[i];
    }
    for (int i = 1; i <= n; i++)
    {
        a[i] = a[i - 1] + a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        if (a[i] < b[i])
        {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
    return;
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
