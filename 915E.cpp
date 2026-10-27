#include <bits/stdc++.h>
using namespace std;
// 定义 set 的节点：[l, r]，v 表示状态（1 表示工作日，2 表示非工作日）
struct Node
{
    int l, r;
    mutable int v; // mutable 允许在 set 内部修改 v 的值

    // 按照左端点排序，set 的标准写法
    bool operator<(const Node &other) const
    {
        return l < other.l;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin>>n>>q;

    set<Node> s;
    // 初始化：整个区间 [1, n] 初始全部是工作日（用 1 表示）
    s.insert({1, n, 1});
    int work_days = n; // 当前总工作日天数

    // 核心操作：分裂区间
    // split(x) 的作用是把包含点 x 的大区间 [l, r] 拆成 [l, x-1] 和 [x, r]
    auto split=[&](int x)
    {
        if (x > n)
            return s.end(); // 超过范围直接返回 end()

        // 1. upper_bound 找到第一个 left > x 的节点，-- 后就是包含 x 的节点
        auto it = --s.upper_bound({x, 0, 0});

        // 2. 如果 x 刚好就是某个节点的左端点，说明已经切过了，不用再切
        if (it->l == x)
            return it;

        // 3. 拿出旧节点的范围和值
        int l = it->l, r = it->r, v = it->v;

        s.erase(it);                      // 删掉原来的大节点 [l, r]
        s.insert({l, x - 1, v});          // 插入切开后的左半边 [l, x - 1]
        return s.insert({x, r, v}).first; // 插入切开后的右半边 [x, r]，并返回它的指针
    };
    // 区间赋值操作：把 [L, R] 统一变成 val (1 或 2)
    auto assign=[&](int L, int R, int val)
    {
        // 细节：必须先 split 右端点 R + 1，再 split 左端点 L！
        // 原因是：如果先 split(L)，得到的迭代器可能在 split(R + 1) 时因为 set 重新结构化而失效（变成野指针）！
        set<Node>::iterator itr = split(R + 1);
        set<Node>::iterator itl = split(L);

        // 遍历 [itl, itr) 之间所有即将被抹掉的小碎片
        for (auto it = itl; it != itr; ++it)
        {
            int len = it->r - it->l + 1;
            if (it->v == 1 && val == 2)
                work_days -= len;
            else if (it->v == 2 && val == 1)
                work_days += len;
        }

        s.erase(itl, itr);     // 抹掉所有旧碎片
        s.insert({L, R, val}); // 插入推平后的全新大区间
    };
    while (q--)
    {
        int l, r, k;
        cin >> l >> r >> k;
        int target_val = (k == 1) ? 2 : 1;

        assign(l, r, target_val);
        cout << work_days << "\n";
    }
    return 0;
}