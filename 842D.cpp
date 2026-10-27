#include<bits/stdc++.h>
using namespace std;
const int MAXN = 300005 * 20;

int tree[MAXN][2];
int pass[MAXN]; 
int tree_cnt = 1;

void insert(int val)
{
    int cur = 1;
    pass[cur]++;
    for (int i = 18; i >= 0; i--)
    {
        int path = (val >> i) & 1;
        if (tree[cur][path] == 0)
        {
            tree[cur][path] = ++tree_cnt;
        }
        cur = tree[cur][path];
        pass[cur]++;
    }
}
int query_mex(int tot)
{
    int cur = 1;
    int res = 0;

    for (int i = 18; i >= 0; i--)//high->low
    {
        int path = (tot >> i) & 1;
        int left_child = tree[cur][path];
        if (left_child != 0 && pass[left_child] == (1 << i))
        {
            res |= (1 << i);
            cur = tree[cur][path ^ 1];
        }
        else
        {
            cur = left_child;
        }
    }
    return res;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin>>n>>m;

    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    for (int x : a)
    {
        insert(x);
    }
    int tot = 0;
    while (m--)
    {
        int x;
        cin >> x;
        tot ^= x; 
        cout << query_mex(tot) << "\n";
    }
    return 0;
}