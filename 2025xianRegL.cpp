#include <bits/stdc++.h>
using namespace std;

#define int long long

void solved()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());
    vector<int> pref(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        pref[i] = pref[i - 1] + a[i];
    }
    vector<int> ans(n + 1, 0);
    int p = n;

    // 4. 从 k = n 倒序处理到 k = 3
    for (int k = n; k >= 3; k--)
    {
        // 如果当前 p 已经小于 k，说明后续更小的 k 也受限于 p，但 p 会随 k 递减，
        // 这里控制 p 不超过当前可选择的上限
        p = min(p, n);

        while (p >= k)
        {
            // 当前选取的 k 根木棍之和为 pref[p] - pref[p - k]
            // 其其余 k-1 根木棍之和为 (pref[p - 1] - pref[p - k])
            int sum_rest = pref[p - 1] - pref[p - k];

            if (a[p] < sum_rest)
            {
                // 满足凸多边形条件，记录答案并结束当前 k 的查找
                ans[k] = pref[p] - pref[p - k];
                break;
            }
            // 不满足条件，指针左移
            p--;
        }

        // 如果没有找到合法 p，则 ans[k] 默认为 0
        if (ans[k] == 0)
        {
            p = k - 1; // 适当重置 p 以供更小的 k 使用
        }
    }
    for (int k = 1; k <= n; k++)
    {
        cout << ans[k] << (k == n ? "" : " ");
    }
    cout << "\n";
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
    {
        solved();
    }
    return 0;
}