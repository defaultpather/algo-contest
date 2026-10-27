
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 k;
    cin >> k;

    string s = "codeforces";
    vector<i64> cnt(10, 1);

    while (true)
    {
        i64 product = 1;

        for (int i = 0; i < 10; i++)
        {
            product *= cnt[i];
            if (product >= k)
                break;
        }

        if (product >= k)
            break;

        int pos = 0;
        for (int i = 1; i < 10; i++)
        {
            if (cnt[i] < cnt[pos])
            {
                pos = i;
            }
        }

        cnt[pos]++;
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < cnt[i]; j++)
        {
            cout << s[i];
        }
    }

    cout << '\n';
    return 0;
}
