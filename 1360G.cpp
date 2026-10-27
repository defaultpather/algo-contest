#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

#define endl '\n'
#define int long long
void solved()
{
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    if (n * a != m * b)
    {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    vector<string> grid(n, string(m, '0'));
    int shift = 0;
    for (int s = 1; s < m; s++)
    {
        if ((s * n) % m == 0)
        {
            shift = s;
            break;
        }
    }
    // 经过 $n$ 次平移后，整体总平移量必须是 $m$ 的整数倍，才能保证 $m$ 个列被均匀地周期性覆盖。
    int cur = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < a; j++)
        {
            grid[i][(cur + j) % m] = '1';
        }
        cur = (cur + shift) % m;
    }
    for (int i = 0; i < n; i++)
    {
        cout << grid[i] << "\n";
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin>>t;
    while (t--)
    {
        solved();
    }
    return 0;
}
