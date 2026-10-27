#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
const int MAXN = 100010 * 42;

int tree[MAXN][2];
int pass[MAXN];
int tree_cnt = 1;
void insert(i64 val)
{
    int cur = 1;
    pass[cur]++;
    for (int i = 40; i >= 0; i--)
    {
        int path = val >> i & 1;
        if (tree[cur][path] == 0)
        {
            tree[cur][path] = ++tree_cnt;
        }
        cur = tree[cur][path];
        pass[cur]++;
    }
}
i64 search(i64 val)
{
    int cur = 1;
    for (int i = 40; i >= 0; i--)
    {
        int path = val >> i & 1;
        if (tree[cur][path] == 0)
        {
            return 0;
        }
        cur = tree[cur][path];
    }
    return 1;
}
void Delete(i64 val)
{
    if (search(val) > 0)
    {
        int cur = 1;
        pass[cur]--;
        for (int i = 40; i >= 0; i--)
        {
            int path = val >> i & 1;
            if (--pass[tree[cur][path]] == 0)
            {
                tree[cur][path] = 0;
                return;
            }
            cur = tree[cur][path];
        }
    }
}
i64 query(i64 val)
{
    int cur = 1;
    i64 res = 0ll;
    for (int i = 40; i >= 0; i--)
    {
        int path = val >> i & 1;
        int best = path ^ 1;
        if (tree[cur][best] != 0)
        {
            res |= 1ll << i;
            cur = tree[cur][best];
        }
        else
        {
            cur = tree[cur][path];
        }
    }
    return res;
}
signed main()
{
    int n;
    cin >> n;
    vector<i64> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    vector<i64> pre(n + 2,0ll), suf(n + 2,0ll);
    for (int i = 1; i <= n; i++)
    {
        pre[i] = pre[i - 1] ^ a[i];
    }
    for (int i = n; i >= 1; i--)
    {
        suf[i] = suf[i + 1] ^ a[i];
    }
    for (int i = 1; i <= n + 1; i++)
    {
        insert(suf[i]);
    }
    i64 max_xor = 0ll;
    for (int i = 0; i <= n; i++)
    {
        if (i >= 1)
            Delete(suf[i]);

        max_xor = max(max_xor, query(pre[i]));
    }
    cout << max_xor << '\n';
}