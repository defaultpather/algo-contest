#include <bits/stdc++.h>
using namespace std;

#define int long long

void solved()
{
    int n;
    cin >> n;
    vector<int> v(n), l(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];
    for (int i = 0; i < n; i++)
        cin >> l[i];
    sort(v.begin(), v.end(), greater<int>());
    sort(l.begin(), l.end());
    auto sv=v,sl=l;
    partial_sum(sv.begin(),sv.end(),sv.begin());
    partial_sum(sl.begin(),sl.end(),sl.begin());
    int q;
    cin >> q;
    while (q--)
    {
        int t;
        cin >> t;
        int lo = 0, hi = n-1  , ans = -1;
        while (lo <= hi)
        {
            int mid=lo+(hi-lo)/2;
            // assert(mid<n);
            if (v[mid] >= t * l[mid])
            {
                ans=mid;
                lo = mid+1;
            }
            else
            {
                hi = mid - 1;
            }
        }
        if (ans < 0)
            cout << 0 << " ";
        else
            cout << sv[ans]-t*sl[ans]<<" ";
    }
    cout << "\n";
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
    {
        solved();
    }
}