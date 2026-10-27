#include <iostream>
#include <vector>

using namespace std;

// 使用 const 定义常量
const int MOD = 998244353;

using Matrix = vector<vector<long long>>;

// 矩阵乘法
Matrix multiply(const Matrix &A, const Matrix &B, int size)
{
    Matrix C(size, vector<long long>(size, 0));
    for (int i = 0; i < size; ++i)
    {
        for (int k = 0; k < size; ++k)
        {
            if (A[i][k] == 0)
                continue;
            for (int j = 0; j < size; ++j)
            {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return C;
}

// 矩阵快速幂: A^p
Matrix power(Matrix A, long long p, int size)
{
    Matrix res(size, vector<long long>(size, 0));
    for (int i = 0; i < size; ++i)
    {
        res[i][i] = 1;
    }
    while (p > 0)
    {
        if (p & 1)
        {
            res = multiply(res, A, size);
        }
        A = multiply(A, A, size);
        p >>= 1;
    }
    return res;
}

// 根据前两个颜色 (c1, c2) 和相对形状 state 还原出一整列 n 个格子的颜色
vector<int> decode_column(int n, int c1, int c2, int state)
{
    vector<int> col(n);
    if (n >= 1)
        col[0] = c1;
    if (n >= 2)
        col[1] = c2;

    for (int i = 2; i < n; ++i)
    {
        int bit = (state >> (i - 2)) & 1;
        if (bit == 0)
        {
            // 填回前前一个格子的颜色
            col[i] = col[i - 2];
        }
        else
        {
            // 填入既不同于 col[i-1] 也不同于 col[i-2] 的第三种颜色
            col[i] = 3 - col[i - 1] - col[i - 2];
        }
    }
    return col;
}

int main()
{
    // 提升读写效率
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long m;
    if (!(cin >> n >> m))
    {
        return 0;
    }

    // 特判 n = 1 的情况
    if (n == 1)
    {
        // 第一格有 3 种填法，之后每一格有 2 种填法
        long long ans = 3;
        long long base = 2;
        long long exp = m - 1;
        while (exp > 0)
        {
            if (exp & 1)
                ans = (ans * base) % MOD;
            base = (base * base) % MOD;
            exp >>= 1;
        }
        cout << ans << "\n";
        return 0;
    }

    // 状态数 S = 2^(n-2)
    int num_states = 1 << (n - 2);
    Matrix M(num_states, vector<long long>(num_states, 0));

    // 构建转移矩阵 M
    // M[i][j] 表示上一列形状为 i（固定前两格为 0, 1），下一列形状为 j 的合法方案数
    for (int i = 0; i < num_states; ++i)
    {
        vector<int> col_prev = decode_column(n, 0, 1, i);

        for (int j = 0; j < num_states; ++j)
        {
            long long valid_ways = 0;

            // 枚举下一列前两个格子的所有合法填法 (c1 != c2)
            for (int c1 = 0; c1 < 3; ++c1)
            {
                for (int c2 = 0; c2 < 3; ++c2)
                {
                    if (c1 == c2)
                        continue;

                    vector<int> col_next = decode_column(n, c1, c2, j);

                    // 检查相邻列在每一行是否都不相同
                    bool is_ok = true;
                    for (int r = 0; r < n; ++r)
                    {
                        if (col_prev[r] == col_next[r])
                        {
                            is_ok = false;
                            break;
                        }
                    }
                    if (is_ok)
                    {
                        valid_ways++;
                    }
                }
            }
            M[i][j] = valid_ways;
        }
    }

    // 计算 M^(m-1)
    Matrix M_pow = power(M, m - 1, num_states);

    // 计算总方案数
    // 初始向量每一个形状对应的具体列方案数为 6
    // 相当于 6 * (矩阵 M^(m-1) 中所有元素之和)
    long long total_sum = 0;
    for (int i = 0; i < num_states; ++i)
    {
        for (int j = 0; j < num_states; ++j)
        {
            total_sum = (total_sum + M_pow[i][j]) % MOD;
        }
    }

    long long final_ans = (total_sum * 6) % MOD;
    cout << final_ans << "\n";

    return 0;
}