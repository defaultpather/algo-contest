#include <bits/stdc++.h>
using namespace std;
#define int long long
bool check(int mid, vector<pair<int, int>> &A)
{
    int n = 1;
    int ex = 0;
    int p = mid;
    for (int i = 0; i < A.size(); i++)
    {
        if (p - A[i].first + (63 - __builtin_clzll(n)) > 60)
        {
            return false;
        }
        n <<= (p - A[i].first - 1);
        if (!A[i].first)
        {
            ex += A[i].second;
            break;
        }
        if (A[i].second > n)
        {
            ex += A[i].second - n;
        }
        else
        {
            n = (n << 1) - A[i].second;
        }
        p = A[i].first;
    }
    return (ex >= n);
}

void solve()
{
    int N;
    cin >> N;
    vector<pair<int, int>> A;
    int lo = 0;
    int hi = 1000000100;
    for (int i = 0; i < N; i++)
    {
        int a, b;
        cin >> a >> b;
        A.push_back({a, b});
        lo = max(lo, a);
    }
    sort(A.rbegin(), A.rend());
    if (A.back().first)
    {
        A.push_back({0, 0});
    }
    while (lo < hi)
    {
        int mid = (lo + hi + 1) / 2;
        if (check(mid, A))
        {
            lo = mid;
        }
        else
        {
            hi = mid - 1;
        }
    }
    cout << lo << endl;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        solve();
    }
}