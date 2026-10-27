#include <bits/stdc++.h>
using namespace std;

using i128 = __int128;
const int mod = 998244353;
__int128 read()
{
    __int128 x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
void print(__int128 x)
{
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}
bool cmp(__int128 x, __int128 y) { return x > y; }
void solve()
{
    i128 n, x;
    n = read(), x = read();
    vector<i128> a(n);
    for (int i = 0; i < n; i++)
        a[i] = read();
    if (x == 1)
    {
        i128 ans = 0;
        for (auto y : a)
            ans = (ans + y) % mod;
        print(ans);
        cout << endl;
        return;
    }
    priority_queue<i128> pq;
    i128 m = 0;
    for (i128 y : a)
    {
        m += y / x;
        y %= x;
        if (y != 0)
        {
            pq.push(y);
        }
    }
    while (!pq.empty() && m >= 0)
    {
        i128 cur = pq.top();
        pq.pop();
        if (m + 1 < x - cur)
        {
            pq.push(cur + m);
            m=0;
            break;
        }
        else
        {
            m -= x - cur - 1;
        }
    }
    i128 ans = 0;
    while (!pq.empty())
    {
        i128 u = pq.top();
        pq.pop();
        ans = (ans + u) % mod;
    }
    if (m > 0)
    {
        ans = (ans + m % (x - 1)) % mod;
    }
    print(ans);
    cout << endl;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        solve();
    }

    return 0;
}