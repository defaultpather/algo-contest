#include <iostream>
#include <vector>
#include<bits/stdc++.h>
using namespace std;

int f(vector<int> &a, vector<int> &s, int sn)
{
    int ans = 0;
    for (int i = 0; i < sn; i++)
    {
        assert(s[i]-1>=0);
        int te = s[i] - 1;
        ans = ans ^ a[te];
    }
    return ans;
}

bool compare(vector<int> &a, int an, vector<int> &b, int bn)
{
    if (an != bn)
        return false;
    for (int i = 0; i < an; i++)
    {
        if (a[i] != b[i])
            return false;
    }
    return true;
}

int main()
{

    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    vector<int> ss(m);
    vector<vector<int>> sa(m);
    vector<int> an(m);
    for (int i = 0; i < m; i++)
    {
        int sn;
        cin >> sn;
        if (sn <= 0)
        {
            return 0;
        }
        an[i] = sn;
        vector<int> s(sn);
        for (int j = 0; j < sn; j++)
        {
            cin >> s[j];
        }
        sa[i] = s;
        ss[i] = f(a, s, sn);
    }

    vector<int> tt(m);
    vector<vector<int>> b(m);
    vector<int> bn(m);
    for (int i = 0; i < m; i++)
    {
        int tn;
        cin >> tn;
        if (tn <= 0)
        {
            return 0;
        }
        bn[i] = tn;
        vector<int> t(tn);
        for (int j = 0; j < tn; j++)
        {
            cin >> t[j];
        }
        b[i] = t;
        tt[i] = f(a, t, tn);
    }

    for (int i = 0; i < m; i++)
    {
        bool fl = (ss[i] == tt[i]);
        if (compare(sa[i], an[i], b[i], bn[i]) == fl)
        {
            cout << "correct\n";
        }
        else
        {
            cout << "wrong\n";
        }
    }
    return 0;
}