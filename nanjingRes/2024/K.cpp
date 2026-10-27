#include <bits/stdc++.h>
using namespace std;

#define int long long

void solved()
{
    int n, m, k, w;
    cin >> n >> m >> k >> w;
    vector<int> red(n), black(m);
    for (int i = 0; i < n; i++)
        cin >> red[i];
    for (int i = 0; i < m; i++)
        cin >> black[i];
    sort(red.begin(), red.end());
    sort(black.begin(), black.end());
    vector<int> cuts;
    cuts.push_back(0);
    for (auto b : black)
    {
        cuts.push_back(b);
    }
    cuts.push_back(w + 1);
    bool ok = 1;
    vector<int> ans;
    for (int cur = 0; cur + 1 < cuts.size(); cur++)
    {
        int L = cuts[cur] + 1;
        int R = cuts[cur + 1] - 1;

        int lo = lower_bound(red.begin(), red.end(), L) - red.begin();
        int hi = upper_bound(red.begin(), red.end(), R) - red.begin();
        vector<int> start;
        int i = lo;
        while (i < hi)
        {
            int pos = red[i];
            start.push_back(pos);
            while (i < hi && i < red.size() && red[i] <= pos + k - 1)
                i++;
        }
        // assert(start.empty());
        if(start.empty()){
            continue;
        }
        int t = (int)start.size();
        if (t * k > R - L + 1)
        {
            ok = false;
            break;
        }
        if (start.back() + k - 1 > R)
        {
            start.back() = R - k + 1;
            for (int j = start.size() - 2; j >= 0; j--)
            {
                if (start[j] + k - 1 >= start[j + 1])
                {
                    start[j] = start[j + 1] - k;
                }
            }
        }
        if (start[0] < L)
        {
            ok = false;
            break;
        }
        for (auto v : start)
        {
            ans.push_back(v);
        }
    }
    if (!ok)
    {
        cout << "-1\n";
    }
    else
    {
        assert(!ans.empty());
        cout << ans.size() << "\n";
        for (int i = 0; i < ans.size(); i++)
        {
            cout << ans[i] << " \n"[i == ans.size() - 1];
        }
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    cin >> t;
    while (t--)
    {
        solved();
    }
}