#include <bits/stdc++.h>
using namespace std;
// #define int long long

const int N = 1000010;
const int MAXN = N * 31;

int tree[MAXN][2];
int pass[MAXN];
int tree_cnt = 1;
void insert(int val)
{
    int cur = 1;
    pass[cur]++;
    for (int i = 30; i >= 0; i--)
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
// 返回与val^的值>=k的前缀异或和有多少个
int query(int val, int k)
{
    int cur = 1;
    int count = 0;
    for (int i = 30; i >= 0; i--)
    {
        if(cur==0)break;
        int path = val >> i & 1;
        int kpath = k >> i & 1;
        if (kpath == 1)
        {
            cur = tree[cur][path ^ 1];
        }
        else
        {
            int best_path = path ^ 1;
            if (tree[cur][best_path] != 0)
            {
                count += pass[tree[cur][best_path]];
            }
            cur = tree[cur][path];
        }
    }
    if (cur != 0)
    {
        count += pass[cur];
    }
    return count;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    insert(0);
    int xor_sum = 0;
    long long ans = 0ll;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        xor_sum ^= x;
        ans += 1ll*query(xor_sum, k);

        insert(xor_sum);
    }
    cout << ans << endl;
}