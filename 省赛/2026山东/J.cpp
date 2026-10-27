#include <bits/stdc++.h>
using namespace std;
template <typename T1, typename T2>
ostream &operator<<(ostream &out, pair<T1, T2> p)
{
    out << "(" << p.first << "," << p.second << ")";
    return out;
}
template <typename T1, typename T2, typename T3>
ostream &operator<<(ostream &out, tuple<T1, T2, T3> p)
{
    out << "(" << get<0>(p) << "," << get<1>(p) << "," << get<2>(p) << ")";
    return out;
}
template <typename T>
ostream &operator<<(ostream &out, vector<T> v)
{
    out << "[";
    if (!v.empty())
        out << v[0];
    for (int i = 1; i < (int)v.size(); i++)
        out << "," << v[i];
    out << "]";
    return out;
}
template <typename T>
ostream &operator<<(ostream &out, set<T> s)
{
    out << vector<T>(s.begin(), s.end());
    return out;
}
template <typename T>
ostream &operator<<(ostream &out, multiset<T> s)
{
    out << vector<T>(s.begin(), s.end());
    return out;
}
template <typename T1, typename T2>
ostream &operator<<(ostream &out, map<T1, T2> s)
{
    out << vector<pair<T1, T2>>(s.begin(), s.end());
    return out;
}

template <typename T1, typename T2>
istream &operator>>(istream &in, pair<T1, T2> &p)
{
    in >> p.first >> p.second;
    return in;
}
template <typename T>
istream &operator>>(istream &in, vector<T> &v)
{
    for (int i = 0; i < (int)v.size(); i++)
        in >> v[i];
    return in;
}

typedef long long ll;
const int mod = 998244353;
void add(int &x, int y)
{
    if ((x += y) >= mod)
        x -= mod;
}
void del(int &x, int y)
{
    if ((x -= y) < 0)
        x += mod;
}

template <typename T>
int gmax(T &x, T y)
{
    if (y > x)
    {
        x = y;
        return 1;
    }
    return 0;
}

template <typename T>
int gmin(T &x, T y)
{
    if (y < x)
    {
        x = y;
        return 1;
    }
    return 0;
}
const int maxn = 4e5 + 10;
struct Treearray
{
    int c[maxn], n;
    void set_n(int _n)
    {
        n = _n;
        for (int i = 1; i <= n; i++)
            c[i] = 0;
    }
    int lowbit(int x) { return x & (-x); }
    void update(int i, int k)
    { // 在i位置加上k
        while (i <= n)
        {
            c[i] += k;
            i += lowbit(i);
        }
    }
    int getsum(int i)
    { // 求A[1 - i]的和
        int res = 0;
        while (i > 0)
        {
            res += c[i];
            i -= lowbit(i);
        }
        return res;
    }
    int query(int l, int r) { return getsum(r) - getsum(l - 1); }
};
Treearray tri;
#define int long long
int solve()
{
    int n;
    cin >> n;
    tri.set_n(n + 5);
    vector<int> a(n + 1);
    vector<int> all;
    for (int i = 1; i <= n; i++)
        cin >> a[i], all.emplace_back(a[i]), tri.update(i, 1);
    reverse(a.begin() + 1, a.end());
    vector<vector<int>> ve(n + 1);
    {
        sort(all.begin(), all.end());
        for (int i = 1; i <= n; i++)
        {
            a[i] = lower_bound(all.begin(), all.end(), a[i]) - all.begin() + 1;
            ve[a[i]].emplace_back(i);
        }
    }
    unordered_map<int, int> dp;
    dp[n + 1] = 0;
    for (int v = n; v >= 1; v--)
    {
        if (ve[v].empty())
            continue;
        unordered_map<int, int> dp2;
        int L = ve[v].front(), R = ve[v].back();
        dp2[L] = 1e18;
        dp2[R] = 1e18;

        for (auto [now, val] : dp)
        {
            if (now < L)
            {
                gmin(dp2[R], val + tri.getsum(R - 1) - tri.getsum(now) + 1);
            }
            else if (now > R)
            {
                gmin(dp2[L], val + tri.getsum(now) - tri.getsum(L) + 1);
            }
            else
            {
                int left = upper_bound(ve[v].begin(), ve[v].end(), now) -
                           lower_bound(ve[v].begin(), ve[v].end(), L);
                int right = upper_bound(ve[v].begin(), ve[v].end(), R) -
                            lower_bound(ve[v].begin(), ve[v].end(), now);

                // cout << "now=" << now << "L=" << L << " R=" << R
                //      << " ve=" << ve[v] << endl;
                // cout << "left=" << left << " right=" << right << endl;
                gmin(dp2[R], val + (tri.query(L, now) - left) * 2 + left +
                                 tri.query(now, R));
                gmin(dp2[L], val + (tri.query(now, R) - right) * 2 + right +
                                 tri.query(L, now));
            }
        }
        // cout << "v=" << v << endl;
        // for (auto [x, y] : dp2) cout << "x=" << x << " y=" << y << endl;
        for (auto it : ve[v])
            tri.update(it, -1);
        dp = dp2;
    }
    int mi = 1e18;
    for (auto [x, v] : dp)
        gmin(mi, v);
    return mi;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--)
        cout << solve() << "\n";
    return 0;
}