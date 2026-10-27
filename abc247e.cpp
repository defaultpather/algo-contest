#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long X, Y;
    if (!(cin >> n >> X >> Y))
        return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }

    long long ans = 0;
    int start = 0;
    int last_X = -1, last_Y = -1;

    for (int i = 0; i < n; ++i)
    {
        if (a[i] < Y || a[i] > X)
        {
            start = i + 1;
            last_X = -1;
            last_Y = -1;
            continue;
        }
        if (a[i] == X)
            last_X = i;
        if (a[i] == Y)
            last_Y = i;

        if (last_X != -1 && last_Y != -1)
        {
            int valid_l = min(last_X, last_Y);
            if (valid_l >= start)
            {
                ans += (valid_l - start + 1);
            }
        }
    }

    cout << ans << "\n";

    return 0;
}