#include<bits/stdc++.h>
using namespace std;

using i64=long long;

struct SegmentTree
{
    struct node
    {
        int l, r; // 区间左右端点 [l, r]
        i64 w;    // 当前区间和 (已取模)
        i64 lazy; // 懒标记（待下传的加法值，已取模）
    };

    vector<i64> w;     // 存储按 DFN 序排列后的初始点权
    vector<node> tree; // 线段树节点数组，大小为 4N
    SegmentTree() {}

#define GL (k << 1)     // 左儿子索引 2k
#define GR (k << 1 | 1) // 右儿子索引 2k + 1

    void init(const vector<i64> &in)
    {
        int n = in.size() - 1; // 1-based 索引
        w.resize(n + 1);
        for (int i = 1; i <= n; i++)
        {
            w[i]=in[i];
        }
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
    // 单节点懒标记作用逻辑
    void pushdown(node &p, i64 lazy_val)
    {
        p.w = p.w + (p.r - p.l + 1) * lazy_val;
        p.lazy = p.lazy + lazy_val;
    }
    // 懒标记下传给左右儿子
    void pushdown(int k)
    {
        if (tree[k].lazy == 0)
            return;
        pushdown(tree[GL], tree[k].lazy);
        pushdown(tree[GR], tree[k].lazy);
        tree[k].lazy = 0;
    }
    void pushup(int k)
    {
        tree[k].w = tree[GL].w + tree[GR].w;
    }

    // 单点修改：在位置 pos 上增加 val（无需懒标记） k表示默认从根开始当前所在的节点位置
    void modify(int pos, i64 val, int k = 1)
    {
        if (tree[k].l == tree[k].r)
        {
            tree[k].w += val; // 到达目标叶子节点，更新权值（覆盖可改写为 tree[k].w = val）
            return;
        }
        int mid = (tree[k].l + tree[k].r) / 2; // 当前到达区间的中点
        if (pos <= mid)
            modify(pos, val, GL); // 目标点在左半区
        else
            modify(pos, val, GR); // 目标点在右半区
        pushup(k);                // 回溯时向上更新祖先节点的和
    }

    // 目标区间修改：[l, r] 加 val  
    void modify(int l, int r, i64 val, int k = 1)//k表示当前所在的结点位置
    {
        if (l <= tree[k].l && tree[k].r <= r)
        {
            pushdown(tree[k], val);
            return;
        }
        pushdown(k);
        int mid = (tree[k].l + tree[k].r) / 2;
        if (l <= mid)
            modify(l, r, val, GL);
        if (mid < r)
            modify(l, r, val, GR);
        pushup(k);
    }

    // 目标区间查询：求 [l, r] 权值和
    i64 ask(int l, int r, int k = 1)
    {
        if (l > r)
            return 0;
        if (l <= tree[k].l && tree[k].r <= r)
        {
            return tree[k].w;
        }
        pushdown(k);
        int mid = (tree[k].l + tree[k].r) / 2;
        i64 ans = 0;
        if (l <= mid)
            ans = ans + ask(l, r, GL);
        if (mid < r)
            ans = ans + ask(l, r, GR);
        return ans;
    }
};