#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

#define endl '\n'
#define int long long

struct node
{
    int l, r;
};
void solved()
{
    int n;
    cin >> n;
    vector<node> a(n + 1);
    vector<int> l, r;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i].l >> a[i].r;
        l.push_back(a[i].l);
        r.push_back(a[i].r);
    }
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    int ans = n;
    for (int i = 1; i <= n; i++)    
    {
        int res = 0;
        auto l1 = upper_bound(l.begin(), l.end(), a[i].r) - l.begin();
        res += n - l1+1;
        auto r1 = lower_bound(r.begin(), r.end(), a[i].l) - r.begin();
        res += r1-1;
        ans = min(ans, res);
    }
    cout << ans << "\n";
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
