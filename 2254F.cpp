#include <bits/stdc++.h>
using namespace std;

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        for (auto &it : a)
            cin >> it;
        for (auto &it : b)
            cin >> it;

        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        if (a == b)
        {
            cout << "YES" << endl;
            continue;
        }

        int x = 0;
        for (auto it : a)
            x ^= it;
        for (auto it : b)
            x ^= it;

        int idx = -1;
        for (int i = 0; i < n; i++)
        {
            if (a[i] == x)
            {
                idx = i;
                break;
            }
        }

        if (idx == -1)
        {
            cout << "NO" << endl;
            continue;
        }

        for (int i = 0; i < n; i++)
        {
            if (i == idx)
                continue;
            a[i] ^= x;
        }

        sort(a.begin(), a.end());
        cout << (a == b ? "YES" : "NO") << endl;
    }
}