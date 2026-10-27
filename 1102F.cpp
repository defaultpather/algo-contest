#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int n, m;
int A[16][10005];
// cost_mid[u][v]: 行 u 和行 v 在同一列上下紧挨着时，差值的最小值
int cost_mid[16][16];
// cost_end[u][v]: 最后一行的 u 在第 c 列，与第一行的 v 在第 c+1 列拼接时，差值的最小值
int cost_end[16][16];
// dp[s][u]: 已经放入集合 s 中的行，且当前最后一行是 u，是否合法
bool dp[1 << 16][16];

bool check(int k)
{
    if (n == 1)
    {
        for (int c = 0; c < m - 1; ++c)
        {
            if (abs(A[0][c] - A[0][c + 1]) < k)
                return false;
        }
        return true;
    }

    // 枚举哪一行作为长序列第一列的起点 (start)
    for (int start = 0; start < n; ++start)
    {
        // 初始化 DP 数组
        for (int s = 0; s < (1 << n); ++s)
        {
            for (int u = 0; u < n; ++u)
                dp[s][u] = false;
        }

        dp[1 << start][start] = true;
        for (int s = 1; s < (1 << n); ++s)
        {
            for (int u = 0; u < n; ++u)
            {
                if (!dp[s][u])
                    continue;
                // 枚举下一个要加入的行 v
                for (int v = 0; v < n; ++v)
                {
                    if (!((s >> v) & 1))
                    { // v 未在集合中
                        // 校验同一列中，行 u 和行 v 上下相邻是否满足 >= k
                        if (cost_mid[u][v] >= k)
                        {
                            dp[s | (1 << v)][v] = true;
                        }
                    }
                }
            }
        }
        // 检查首尾拼接条件：最后一行的 last 与 第一行的 start
        int all_mask = (1 << n) - 1;
        for (int last = 0; last < n; ++last)
        {
            // 如果所有行都已用完，且满足第 c 列最后一行 -> 第 c+1 列第一行的差值 >= k
            if (dp[all_mask][last] && cost_end[last][start] >= k)
            {
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

    if (!(cin >> n >> m))
        return 0;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> A[i][j];
        }
    }

    // 预处理 1：同一列中，上下相邻两行的最小差值 cost_mid[i][j]
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i == j)
                continue;
            int mn = 2e9;
            for (int c = 0; c < m; ++c)
            {
                mn = min(mn, abs(A[i][c] - A[j][c]));
            }
            cost_mid[i][j] = mn;
        }
    }

    // 预处理 2：换列时，上一列最后一行 i 与 下一列第一行 j 的最小差值 cost_end[i][j]
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i == j && n > 1)
                continue;
            int mn = 2e9;
            for (int c = 0; c < m - 1; ++c)
            {
                mn = min(mn, abs(A[i][c] - A[j][c + 1]));
            }
            cost_end[i][j] = mn;
        }
    }

    // 二分答案 k
    int l = 0, r = 1e9, ans = 0;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (check(mid))
        {
            ans = mid;
            l = mid + 1; // 尝试寻找更大的 k
        }
        else
        {
            r = mid - 1;
        }
    }

    cout << ans << "\n";
    return 0;
}