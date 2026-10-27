#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    cin >> t;
    while (t--)
    {
        string s;
        cin >> s;
        for (int i = 0; i < s.size(); i++)
        {
            if (i & 1)
            {
                if (s[i] == '1')
                {
                    s[i] = '0';
                }
                else if (s[i] == '0')
                {
                    s[i] = '1';
                }
            }
        }
        stack<char> stk;
        for (int i = 0; i < s.size(); i++)
        {
            if (!stk.empty())
            {
                if ((stk.top() == '0' && s[i] == '1') || (stk.top() == '1' && s[i] == '0'))
                {
                    stk.pop();
                    continue;
                }
            }
            stk.push(s[i]);
        }
        vector<int> a;
        while (!stk.empty())
        {
            a.push_back(stk.top() - '0');
            stk.pop();
        }
        reverse(a.begin(), a.end());
        int c0 = count(a.begin(), a.end(), 0);
        int c1 = count(a.begin(), a.end(), 1);
        int c2 = count(a.begin(), a.end(), 2);
        if (c0 > c1)
            swap(c0, c1);
        if (c0 + c2 > c1)
        {
            cout << (c2 + c0 - c1) % 2 << "\n";
        }
        else
        {
            cout << c1 - (c0 + c2) << "\n";
        }
    }
}

// 0100202010
// 0001212111
// 0001010111