#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

void solved()
{
    i64 n, k;
    cin >> n >> k;
    if (k >= 200000)
    {
        cout << -1 << "\n";
        return;
    }
    i64 need = k * (k + 1) / 2;
    if (n < need)
    {
        cout << -1 << "\n";
        return;
    }
    i64 max_g = -1;
    for (i64 i = 1; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            i64 d1 = i;
            i64 d2 = n / i;
            if (n / d1 >= need)
            {
                max_g = max(max_g, d1);
            }
            if (n / d2 >= need)
            {
                max_g = max(max_g, d2);
            }
        }
    }
    if (max_g == -1)
    {
        cout << -1 << "\n";
        return;
    }
    i64 sum = 0;
    for (int i = 1; i < k; i++)
    {
        i64 val = i * max_g;
        cout << val << " ";
        sum += val;
    }
    cout << (n - sum) << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solved();

    return 0;
}