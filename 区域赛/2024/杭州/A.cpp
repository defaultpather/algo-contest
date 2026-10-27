#include <bits/stdc++.h>
using namespace std;

void solved()
{
    string A, B, C;
    cin >> A >> B >> C;

    if (A.size() != B.size())
    {
        cout << "NO\n";
        return;
    }
    if (A.size() != C.size())
    {
        cout << "YES\n";
        return;
    }

    int n = A.size();
    int par[26];
    for (int i = 0; i < 26; i++)
        par[i] = i;

    auto find = [&](int x)
    {
        while (par[x] != x)
        {
            par[x] = par[par[x]];
            x = par[x];
        }
        return x;
    };
    auto uni = [&](int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a != b)
            par[a] = b;
    };
    for (int i = 0; i < n; i++)
        uni(A[i] - 'a', B[i] - 'a');
    bool ok = false;
    for (int i = 0; i < n; i++)
    {
        if (find(C[i] - 'a') != find(A[i] - 'a'))
        {
            ok = true;
            break;
        }
    }
    cout << (ok ? "YES\n" : "NO\n");
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        solved();
    return 0;
}