#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
int a[300005][8];
int ans_i = 1, ans_j = 1;
bool check(int x, bool save_ans = false)
{
    // has_mask[mask] 存储二进制掩码 mask 对应的某一个数组下标（1-based）
    vector<int> has_mask(1 << m, -1);

    for (int i = 0; i < n; ++i)
    {
        int mask = 0;
        for (int k = 0; k < m; ++k)
        {
            if (a[i][k] >= x)
            {
                mask |= (1 << k);
            }
        }
        has_mask[mask] = i + 1; // 记录该 mask 对应的数组下标
    }

    int target = (1 << m) - 1; // 全 1 掩码
    
    // 枚举所有可能的 mask 组合
    for (int m1 = 0; m1 < (1 << m); ++m1)
    {
        if (has_mask[m1] == -1)
            continue;
        for (int m2 = 0; m2 < (1 << m); ++m2)
        {
            if (has_mask[m2] == -1)
                continue;

            if ((m1 | m2) == target)
            {
                if (save_ans)
                {
                    ans_i = has_mask[m1];
                    ans_j = has_mask[m2];
                }
                return true;
            }
        }
    }

    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>m;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> a[i][j];
        }
    }

    int l = 0, r = 1e9, best_x = 0;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (check(mid))
        {
            best_x = mid;
            l = mid + 1; 
        }
        else
        {
            r = mid - 1;
        }
    }
    check(best_x, true);

    cout << ans_i << " " << ans_j << "\n";

    return 0;
}