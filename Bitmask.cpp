#include <bits/stdc++.h>
using namespace std;
const int B = 30;
const int N = 3e5 + 10;
int a[N];
int cnt[B][4];
int trans[B][4];
signed main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < B; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int bit = (a[j] >> i) & 1;
            int nxt_bit = (i + 1 >= B ? 0 : ((a[j] >> (i + 1)) & 1));
            int val = (nxt_bit << 1) | bit;
            cnt[i][val]++;
        }
        for (int s = 0; s < 4; s++)
        {
            trans[i][s] = s;
        }
    }
    int m;
    cin >> m;
    while (m--)
    {
        int type, x;
        cin >> type >> x;
        int ans = 0;
        for (int i = 0; i < B; i++)
        {
            int bit = (x >> i )& 1;
            int nxt_bit = (i + 1 >= B ? 0 : (x >> (i + 1)) & 1);
            int val = (nxt_bit << 1) | bit;
            int ops[4];
            for (int s = 0; s < 4; s++)
            {
                if (type == 1)
                {
                    ops[s] = s & val;
                }
                else if (type == 2)
                {
                    ops[s] = s | val;
                }
                else if (type == 3)
                {
                    ops[s] = s ^ val;
                }
            }
            for (int s = 0; s < 4; s++)
            {
                trans[i][s] = ops[trans[i][s]];
                if (trans[i][s] == 1)
                {
                    ans += cnt[i][s];
                }
            }
        }
        cout << ans << endl;
    }
}