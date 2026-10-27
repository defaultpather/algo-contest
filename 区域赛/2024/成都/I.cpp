#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int primes[N]; 

struct SegmentTree
{
    struct node
    {
        int l, r;
        int w; 
        int lazy;
    };

    vector<int> w;
    vector<node> tree;

    SegmentTree() {}

#define GL (k << 1)
#define GR (k << 1 | 1)

    void init(const vector<int> &in)
    {
        int n = in.size() - 1;
        w.resize(n + 1);
        for (int i = 1; i <= n; i++)
            w[i] = in[i];
        tree.resize(n * 4 + 1);
        auto build = [&](auto self, int l, int r, int k = 1) -> void
        {
            if (l == r)
            {
                tree[k] = {l, r, w[l], 0};
                return;
            }
            tree[k] = {l, r, 0, 0};
            int mid = (l + r) / 2;
            self(self, l, mid, GL);
            self(self, mid + 1, r, GR);
            pushup(k);
        };
        build(build, 1, n);
    }

    void pushup(int k)
    {
        tree[k].w = __gcd(tree[GL].w, tree[GR].w);
    }
    void modify(int pos, int val, int k = 1)
    {
        if (tree[k].l == tree[k].r)
        {
            tree[k].w = val;
            return;
        }
        int mid = (tree[k].l + tree[k].r) / 2;
        if (pos <= mid)
            modify(pos, val, GL);
        else
            modify(pos, val, GR);
        pushup(k);
    }
    int root_gcd() const { return tree[1].w; }
};

void init()
{
    for (int i = 1; i < N; i++)
        for (int j = i; j < N; j += i)
            primes[j]++;
}

void solved()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    primes[0] = n; 
    vector<int> b(n + 1, 0);
    for (int i = 1; i + 1 <= n; i++)
        if (a[i] > a[i + 1])
            b[i] = i;

    SegmentTree sgt;
    sgt.init(b);
    cout<<primes[sgt.tree[1].w]<<"\n";
    while (q--)
    {
        int p, v;
        cin >> p >> v;

        a[p] = v; 
        if (p - 1 >= 1 && p - 1 <= n - 1)
            sgt.modify(p - 1, (a[p - 1] > a[p]) ? p - 1 : 0);
        if (p >= 1 && p <= n - 1)
            sgt.modify(p, (a[p] > a[p + 1]) ? p : 0);

        cout << primes[sgt.root_gcd()] << '\n'; 
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    cin >> t;
    init();
    while (t--)
        solved();
    return 0;
}