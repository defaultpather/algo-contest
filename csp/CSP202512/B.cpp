#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> k(m + 1);
    for (int i = 1; i <= m; i++)
    {
        cin >> k[i];
    }
    auto F = [&](int X, int K) -> int
    {
        return ((X * X + K * K) % 8) ^ K;
    };
    auto G = [&](int X, int K) -> int
    {
        int c = (X & ((1 << 3) - 1));
        int b = ((X >> 3) & ((1 << 3) - 1));
        int a = ((X >> 6) & ((1 << 3) - 1));
        // cout<<"a="<<a<<" b="<<b<<" c="<<c<<endl;
        int newA = b;
        int newB = (c ^ F(b, K));
        int newC = (a ^ F(c, K));
        // cout << "newA=" << newA << " newB=" << newB << " newC=" << newC << endl;
        int res = (newA << 6) | (newB << 3) | newC;
        // cout<<"res="<<res<<endl;
        return res;
    };
    vector<int> f(m + 1);
    vector<int> ans(1 << 10);
    for (int mask = 0; mask < (1 << 9); mask++)
    {
        f[0] = mask;
        for (int i = 1; i <= m; i++)
        {
            f[i] = G(f[i - 1], k[i]);
        }
        ans[f[m]] = mask;
    }
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        cout << ans[a] << " \n"[i == n - 1];
    }
}
