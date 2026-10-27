
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

mt19937_64 rng(
    chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r)
{
    return uniform_int_distribution<int>(l, r)(rng);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 操作数量：小数据和大数据随机切换
    int mode = rnd(1, 10);
    int n;

    if (mode <= 3)
        n = rnd(1, 20);
    else if (mode <= 7)
        n = rnd(50, 500);
    else
        n = rnd(5000, 20000);

    // 元素值范围较大
    const int V = 1000000000;

    vector<pair<char, int>> ops;
    vector<int> stk;

    // 记录栈中元素，保证互异
    unordered_set<int> inStack;
    inStack.reserve(n * 2 + 10);

    auto push = [&](int x)
    {
        stk.push_back(x);
        inStack.insert(x);
        ops.emplace_back('+', x);
    };

    auto pop = [&]()
    {
        inStack.erase(stk.back());
        stk.pop_back();
    };

    for (int i = 0; i < n; i++)
    {
        int op = rnd(0, 99);

        // 30%：尝试压栈
        if (op < 30 && (int)stk.size() < n)
        {
            int x;
            do
            {
                x = rnd(1, V);
            } while (inStack.count(x));

            push(x);
        }
        // 20%：模拟弹栈，不输出弹栈操作
        else if (op < 50 && !stk.empty())
        {
            pop();
        }
        // 25%：生成 T，查询一个当前在栈中的元素
        else if (op < 75 && !stk.empty())
        {
            int pos = rnd(0, (int)stk.size() - 1);
            ops.emplace_back('T', stk[pos]);
        }
        // 其余：生成 F，查询一个不在栈中的元素
        else
        {
            int x;
            do
            {
                x = rnd(1, V);
            } while (inStack.count(x));

            ops.emplace_back('F', x);
        }
    }

    cout << ops.size() << '\n';
    for (auto [c, x] : ops)
        cout << c << ' ' << x << '\n';

    return 0;
}
