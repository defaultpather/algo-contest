#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long
#define lowbit(x) (x& -x)
struct BIT
{
    int n;
    vector<int> tree;
    BIT(int n) : n(n), tree(n + 1, 0) {}

    void add(int i, int delta)
    {
        for (; i <= n; i += i & -i)
            tree[i] += delta;
    }

    int query(int i)
    {
        int sum = 0;
        for (; i > 0; i -= i & -i)
            sum += tree[i];
        return sum;
    }

    int query_range(int l, int r)
    {
        if (l > r)
            return 0;
        return query(r) - query(l - 1);
    }
};
void solved(){
    int n;
    string s;
    cin>>n>>s;
    vector<int> pos[26];
    for (int i = 0; i < n; ++i)
    {
        pos[s[i] - 'a'].push_back(i + 1);
    }

    vector<int> ptr(26, 0);
    string t = s;
    reverse(t.begin(), t.end());

    vector<int> p(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        int c = t[i - 1] - 'a';
        int orig_idx = pos[c][ptr[c]++];
        p[orig_idx] = i; 
    }
    BIT bit(n);
    int ans = 0;
    for (int i = 1; i <= n; ++i){
        ans += bit.query_range(p[i] + 1, n);
        bit.add(p[i], 1);
    }
    cout << ans << "\n";
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T=1;
    // cin>>T;
    while(T--){
       solved();
    }
    return 0;
}
