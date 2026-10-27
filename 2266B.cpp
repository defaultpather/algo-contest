#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

#define endl '\n'
#define int long long
void solved()
{
    int a, b, c;
    cin >> a >> b >> c;
    if (a < b)
    {
        if (abs(a - b) < abs(a + c - b))
        {
            cout << abs(a + c - b) << endl;
        }
        else
        {
            cout << abs(a - b) << endl;
        }
    }
    else
    {
        cout << abs(a + c - b) << endl;
    }
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
