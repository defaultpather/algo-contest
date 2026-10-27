#include <bits/stdc++.h>
using namespace std;

#define int long long
const int mod = 1e9 + 7;
const int B = 20;        // 2^20 = 1048576 > 10^6
const int MAXN = 1 << B; // 1048576

int p[MAXN + 5];
int a[MAXN + 5];

void solved()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        a[x]++;
    }

    for (int j = 0; j < B; j++){
        for (int i = 0; i < MAXN; i++)
        {
            if (!((i >> j) & 1))
            {
                a[i] = (a[i] + a[i ^ (1 << j)]) % mod;
            }
        }
    }

    int ans = 0;
    for (int mask = 0; mask < MAXN; mask++)
    {
        if (a[mask] == 0)
            continue; 

        int cnt = (p[a[mask]] - 1 + mod) % mod; // 包含了 mask 的非空子序列方案数

        if (__builtin_popcount(mask) % 2 == 1)
        {
            ans = (ans - cnt + mod) % mod; // 奇数个 1 减去
        }
        else
        {
            ans = (ans + cnt) % mod; // 偶数个 1 加上
        }
    }

    cout << ans << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    p[0] = 1;
    for (int i = 1; i < MAXN; i++)
    {
        p[i] = (p[i - 1] << 1) % mod;
    }

    solved();
    return 0;
}