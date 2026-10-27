#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve()
{
    int n;
    ll k;
    cin >> n >> k;
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    vector<ll> S(n + 1, 0), g(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        S[i] = S[i - 1] + a[i];
        g[i] = a[i] - k * i;
    }
    // for(int i=0;i<n;i++){
    //     cout<<a[i]<<endl;
    // }
    for(int i=1;i<=n;i++){
        if (i == 1 || i == n)
        { 
            cout << 0 << " \n"[i == n];
            continue;
        }
        ll thr = g[i - 1] - k; 
        int lo = i + 1, hi = n, B = i;
        while (lo <= hi)
        { 
            int mid = (lo + hi) / 2;
            if (g[mid] > thr)
            {
                B = mid;
                lo = mid + 1;
            }
            else
                hi = mid - 1;
        }
        if (B < i + 1)
        {
            cout << 0 << " \n"[i == n];
            continue;
        }
        ll t = B - i; 
        ll ans = (S[B] - S[i]) - t * a[i - 1] - k * t * (t + 1) / 2;
        cout << ans << " \n"[i == n];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}