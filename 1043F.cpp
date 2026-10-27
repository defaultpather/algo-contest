/**
 *    author:  tourist
 *    created: 28.10.2018 19:02:44
 **/
#include <bits/stdc++.h>

using namespace std;

int main()
{
    // 解绑 cin/cout 提高输入输出效率
    ios::sync_with_stdio(false);
    cin.tie(0);

    const int MAX = 300010; // 定义数值范围上限，题目给定的最大数值约为 3e5
    vector<int> p(MAX);
    iota(p.begin(), p.end(), 0); // 将 p 数组初始化为 0, 1, 2, ..., MAX-1

    // 线性/埃氏筛预处理：用 p[i] 记录数字 i 的最小质因子（Smallest Prime Factor, SPF）
    for (int i = 2; i < MAX; i++)
    {
        if (p[i] == i)
        { // 如果 p[i] == i，说明 i 是质数
            for (int j = i + i; j < MAX; j += i)
            {
                if (p[j] == j)
                {             // 只有在 j 还没被更小的质因子标记过时才更新
                    p[j] = i; // 将 j 的最小质因子设为 i
                }
            }
        }
    }

    int n;
    cin >> n; // 读取输入的元素个数

    vector<int> has(MAX, 0);  // has[x] 记录数值 x 是否在输入数组中出现过
    vector<vector<int>> d(n); // d[i] 存储第 i 个数分解质因数后得到的“互不相同的质因子列表”
    int g = 0;                // 记录所有输入元素的整体最大公约数 GCD

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        g = __gcd(g, x); // 累加计算全局 GCD
        has[x] = 1;      // 标记数字 x 出现过

        // 利用预处理好的最小质因子 p[x]，对 x 进行质因数分解
        while (x > 1)
        {
            // 避免重复加入相同的质因子（比如 12 = 2*2*3，质因子列表只存 [2, 3]）
            if (d[i].empty() || d[i].back() != p[x])
            {
                d[i].push_back(p[x]);
            }
            x /= p[x]; // 除以最小质因子，继续分解
        }
    }

    // 剪枝判定：如果全局所有数的 GCD > 1，说明无论选多少个数都不可能凑出 GCD 为 1，直接输出 -1
    if (g > 1)
    {
        cout << -1 << '\n';
        return 0;
    }

    // 预处理高维倍数关系：更新后 has[i] 表示整个数组中“能被 i 整除的数字个数”
    for (int i = 1; i < MAX; i++)
    {
        for (int j = i + i; j < MAX; j += i)
        {
            has[i] += has[j];
        }
    }

    int ans = n + 1; // 最终答案初始化为一个极大值（最多选 n 个数）

    // 核心遍历：枚举选出的数集中“包含第 i 个数”作为基准数
    for (int i = 0; i < n; i++)
    {
        int sz = (int)d[i].size(); // 当前基准数包含的质因子个数 sz（因为 MAX=3e5，sz 最多为 7）
        vector<int> cnt(1 << sz);  // cnt[t] 用于存储状态 t 对应的统计信息

        // 1. 初始化 cnt 数组
        // 状态 t 的二进制掩码：第 j 位为 1 代表选中 d[i][j] 这个质因子
        for (int t = 0; t < (1 << sz); t++)
        {
            int u = 1;
            for (int j = 0; j < sz; j++)
            {
                if (t & (1 << j))
                {
                    u *= d[i][j]; // 将选中的质因子相乘得到 u
                }
            }
            cnt[t] = has[u]; // cnt[t] 初始记录：能被 u（即这组质因子的乘积）整除的数有多少个 同时可能有比u乘积更多的质因子
        }
        //至少包含掩码中所有质因子的数的个数

        // 2. SOS DP（子集高维超集差分）：剥离包含更多质因子的影响
        for (int bit = 0; bit < sz; bit++)
        {
            for (int t = 0; t < (1 << sz); t++)
            {
                if (t & (1 << bit))
                {
                    cnt[t ^ (1 << bit)] -= cnt[t]; // 计算超集差，消除包含更大质因子集合的重叠计数
                }
            }
        }//只包含掩码中....

        // 3. SOS DP（子集高维前缀和）：累加子集方案数
        for (int bit = 0; bit < sz; bit++)
        {
            for (int t = 0; t < (1 << sz); t++)
            {
                if (t & (1 << bit))
                {
                    cnt[t] += cnt[t ^ (1 << bit)]; // 组合出准确的子集覆盖计数
                }
            }
        }//包含的质因子是t的子集的个数

        // 经过上述两次变换后：
        // cnt[mask] 正确表达了“能消去质因子 子集 mask 的数字在原数组中的个数”

        // 4. 状压 DP 求解子集覆盖问题（求解消去 d[i] 所有质因子所需的最少数）
        vector<int> dp(1 << sz);
        dp[0] = 1; // 初始状态：只有基准数 d[i] 自己，消去的质因子集合为空（0），已使用 1 个数

        // 遍历所有可能的质因子消去状态 t
        for (int t = 1; t < (1 << sz); t++)
        {
            dp[t] = n + 1; // 初始化为极大值
            int u = t;

            // 位运算技巧：高效遍历状态 t 的所有子集 u
            while (u > 0)
            {
                // (1 << sz) - 1 - u 表示子集 u 在全集中的补集
                // cnt[补集] > 0 说明原数组中存在能够一次性帮我们消去质因子子集 u 的数字
                if (cnt[(1 << sz) - 1 - u] > 0)
                {
                    dp[t] = min(dp[t], dp[t - u] + 1); // 状态转移：从消去 t-u 的代价 + 1 转移过来
                }
                u = (u - 1) & t; // 经典位运算：获取 t 的下一个子集
            }
        }

        // dp[(1 << sz) - 1] 表示消去 d[i] 的“所有质因子”需要的最小数字个数
        ans = min(ans, dp[(1 << sz) - 1]); // 更新全局最优解
    }

    cout << ans << '\n'; // 输出最终答案
    return 0;
}