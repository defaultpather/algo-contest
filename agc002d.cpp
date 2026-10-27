#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const int MAXN = 100010;
const int MAXM = 100010;

// 原图的边结构体
struct Edge
{
    int u, v; // 边的两个端点（编号从 1 到 m，天然代表加入顺序）
} edges[MAXM];

// 询问结构体
struct Query
{
    int u, v; // 起点 u 和起点 y
    int z;    // 要求的最少可达点数
    int id;   // 原始询问编号，用于按顺序输出答案
};

int ans[MAXN]; // 存储每个询问的最终答案
int n, m, q;

// ==================== 1. 可撤销并查集 ====================
struct RollbackDSU
{
    int fa[MAXN]; // 父节点数组
    int sz[MAXN]; // 连通块的大小（包含的点数）

    // 用于历史记录的结构体
    struct History
    {
        int u, v;   // 被合并的两个根节点（v 连到了 u 上）
        int su, sv; // 合并前 u 和 v 各自的 sz 值
    };
    vector<History> history; // 历史操作栈

    // 初始化并查集
    void init(int n)
    {
        for (int i = 1; i <= n; i++)
        {
            fa[i] = i; // 每个点初始父节点为自己
            sz[i] = 1; // 初始连通块大小为 1
        }
        history.clear();
    }

    // 查找根节点（注意：不可使用路径压缩！必须保持树的原始形态才能撤销）
    int find(int u)
    {
        while (u != fa[u])
            u = fa[u];
        return u;
    }

    // 按秩合并（按连通块大小合并）
    void merge(int u, int v)
    {
        u = find(u);
        v = find(v);
        if (u == v)
            return; // 已经在同一连通块，无需合并

        // 启发式合并：总是把小树合并到大树上，保证树的高度为 O(log N)
        if (sz[u] < sz[v])
            swap(u, v);

        // 记录合并前的状态入栈，以便后续撤销
        history.push_back({u, v, sz[u], sz[v]});

        fa[v] = u;      // 将 v 的根指向 u
        sz[u] += sz[v]; // 更新 u 的连通块大小
    }

    // 查询点 u 所在连通块的大小
    int get_size(int u)
    {
        return sz[find(u)];
    }

    // 获取当前历史栈的大小（相当于打一个状态快照）
    int history_size()
    {
        return history.size();
    }

    // 回滚撤销操作：回滚到历史栈大小为 target_size 的状态
    void rollback(int target_size)
    {
        while ((int)history.size() > target_size)
        {
            auto h = history.back();
            history.pop_back();

            // 还原父节点和连通块大小
            fa[h.v] = h.v;
            sz[h.u] = h.su;
            sz[h.v] = h.sv;
        }
    }
} dsu;

// ==================== 2. 整体二分核心逻辑 ====================
// solve(l, r, q_list) 表示当前在二分答案区间 [l, r]，q_list 是属于该区间的询问列表
void solve(int l, int r, vector<Query> &q_list)
{
    // 递归边界 1：如果当前区间没有询问，直接返回
    if (q_list.empty())
        return;

    // 递归边界 2：如果区间缩小为一个点 [l, l]，说明找到答案就是 l
    if (l == r)
    {
        for (const auto &qry : q_list)
        {
            ans[qry.id] = l; // 记录答案
        }
        return;
    }

    int mid = (l + r) >> 1; // 取边的编号中点

    // 保存当前并查集的快照（记录此时的历史栈深度）
    int snapshot = dsu.history_size();

    // 【关键步骤 1】：把第 l 到第 mid 条边依次加入并查集
    for (int i = l; i <= mid; i++)
    {
        dsu.merge(edges[i].u, edges[i].v);
    }

    vector<Query> left_q;  // 答案在 [l, mid] 的询问
    vector<Query> right_q; // 答案在 [mid + 1, r] 的询问

    // 【关键步骤 2】：判定当前询问列表中的各个询问
    for (const auto &qry : q_list)
    {
        int fu = dsu.find(qry.u);
        int fv = dsu.find(qry.v);
        int total_sz = 0;

        // 如果 u 和 v 在同一个连通块内，并集大小就是该连通块大小
        if (fu == fv)
        {
            total_sz = dsu.get_size(fu);
        }
        else
        {
            // 如果不在同一个连通块，并集大小为两连通块大小之和
            total_sz = dsu.get_size(fu) + dsu.get_size(fv);
        }

        // 判定条件：连通块点数之和是否满足要求 z
        if (total_sz >= qry.z)
        {
            left_q.push_back(qry); // 满足要求，说明答案 <= mid
        }
        else
        {
            right_q.push_back(qry); // 不满足要求，说明答案 > mid
        }
    }

    // 【关键步骤 3】：递归解决右半部分 [mid + 1, r]
    // 注意：右半部分的二分需要保留 [l, mid] 的边（因为右侧询问需要包含前 mid 条边的连通性）
    solve(mid + 1, r, right_q);

    // 【关键步骤 4】：回滚并查集，撤销 [l, mid] 加入的边
    dsu.rollback(snapshot);

    // 【关键步骤 5】：递归解决左半部分 [l, mid]
    solve(l, mid, left_q);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> edges[i].u >> edges[i].v;
    }

    cin >> q;
    vector<Query> q_list(q);
    for (int i = 0; i < q; i++)
    {
        cin >> q_list[i].u >> q_list[i].v >> q_list[i].z;
        q_list[i].id = i; // 保存原始顺序
    }

    // 初始化并查集
    dsu.init(n);

    // 开启整体二分，初始边编号区间为 [1, m]
    solve(1, m, q_list);

    // 按顺序输出每个询问的结果
    for (int i = 0; i < q; i++)
    {
        cout << ans[i] << endl;
    }

    return 0;
}