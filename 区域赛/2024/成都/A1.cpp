#include <bits/stdc++.h>
using namespace std;

#define int long long
void solved()
{
    string s;
    cin >> s;
    int n = s.size();
    bool ok = 1;
    for (int i = n - 1; i >= 0; i--)
    {
        if (s[i] == '-' && (n - 1 - i + 1) <= 3)
        {
            ok = 0;
            break;
        }
    }

    if (s[0] != '>' || count(s.begin(), s.end(), '-') == 0 || !ok)
    {
        cout << "No\n";
        return;
    }
    // cout<<"Yes\n";
    int ed = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        if (s[i] != '>')
        {
            ed = i;
            break;
        }
    }
    ed++;
    int len = (n - 1 - ed + 1);
    vector<int> l;
    for (int i = 0; i < ed; i++)
    {
        if (s[i] == '>')
        {
            l.push_back(i);
        }
    }
    int cnt = max((len + 2) / 3, (int)l.size());

    while (l.size() < cnt)
    {
        l.push_back(l.back());
    }
    cout << "Yes " << cnt << endl;
    for (int i = 0; i < cnt; i++)
    {
        int r = max(n - 3 * i, ed + 3);
        int len = r - l[i];
        cout << l[i] + 1 << " " << len << endl;
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