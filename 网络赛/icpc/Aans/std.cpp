#include <bits/stdc++.h>
    using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--)
    {
        int n;
        cin >> n;

        vector<pair<char, int>> ops(n);

        for (int i = 0; i < n; i++)
        {
            char c;
            cin >> c;

            if (c == '+')
            {
                int x;
                cin >> x;
                ops[i] = {c, x};
            }
            else
            {
                int x;
                cin >> x;
                ops[i] = {c, x};
            }
        }

        vector<int> stk;
        string ans;

        auto pop_stack = [&]()
        {
            stk.pop_back();
            ans += '-';
        };

        auto contains = [&](int x)
        {
            return find(stk.begin(), stk.end(), x) != stk.end();
        };

        for (auto [c, x] : ops)
        {
            if (c == '+')
            {
                // 如果 x 已经在栈中，先弹出直到 x 被移除
                while (contains(x))
                {
                    pop_stack();
                }

                stk.push_back(x);
                ans += '+';
            }
            else if (c == 'T')
            {
                // x 必须存在：弹出 x 上方的所有元素
                while (stk.back() != x)
                {
                    pop_stack();
                }

                ans += '?';
            }
            else
            {
                // F x：确保 x 不在栈中
                while (contains(x))
                {
                    pop_stack();
                }

                ans += '?';
            }
        }

        cout << ans << '\n';
    }

    return 0;
}