#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll INF = (ll)4e18; // 定义无穷大常量，用于初始化最小值

// 树的全局/局部变量声明
int n, m;
vector<ll> c;            // 存放每个节点的购买费用 c[i]
vector<vector<int>> adj; // 邻接表存图

vector<int> parent_node; // 每个节点的父节点 parent_node[u]
vector<int> tin, tout;   // DFS 进出时间戳，用于 O(1) 判断祖先关系
int timer_cnt;           // DFS 时间戳计数器

vector<ll> A;        // A[v] 表示获取节点 v 的最小代价（直接买或用两个子节点合成）
vector<ll> mn1, mn2; // mn1[v] 和 mn2[v] 分别表示节点 v 的所有子节点中 A 值的最小值与次小值
vector<int> arg1;    // arg1[v] 记录 A 值最小的那个子节点编号
vector<ll> pre;      // pre[v] 记录从根节点 1 到节点 v 的路径上，每次向上合成所需的“最优兄弟节点”的累计代价

// 第一次 DFS：建立父子关系、记录 DFS 时间戳、自底向上计算 A[u] 和子节点最小值
void dfs_calc(int u, int p)
{
    parent_node[u] = p;   // 记录 u 的父节点
    tin[u] = ++timer_cnt; // 记录进入节点 u 的时间戳

    ll m1 = INF, m2 = INF; // 初始化 u 的子节点 A 值最小值 m1 和次小值 m2
    int a1 = 0;            // 初始化最小 A 值对应的子节点编号

    // 遍历 u 的所有邻接节点
    for (int v : adj[u])
    {
        if (v == p)
            continue;
        dfs_calc(v, u); //后序遍历
        ll val = A[v]; // 子节点 v 的最小获取代价
        // 动态维护子节点 A 值的最小值 m1 和次小值 m2
        if (val < m1){
            m2 = m1;
            m1 = val;
            a1 = v; // 记录产生最小值 m1 的节点 v
        }
        else if (val < m2)
        {
            m2 = val;
        }
    }

    // 保存 u 的子节点极值信息
    mn1[u] = m1;
    mn2[u] = m2;
    arg1[u] = a1;

    // 状态转移计算 A[u]
    if (a1 == 0)
    {
        A[u] = c[u]; // 如果是叶子节点（没有子节点），只能直接支付 c[u] 购买
    }
    else
    {
        A[u] = min(c[u], m1 + m2); // 非叶节点：可以直接买 c[u]，或者合成两个最便宜的子节点 (m1 + m2)
    }

    tout[u] = timer_cnt; // 记录离开节点 u（子树遍历结束）的时间戳
}

// 第二次 DFS：自顶向下计算前缀和 pre[u]
void dfs_pre(int u, int p)
{
    // 遍历 u 的所有子节点
    for (int v : adj[u])
    {
        if (v == p)
            continue; // 跳过父节点

        // 从子节点 v 向上合并到父节点 u 时，需要额外购买 u 的另一个子节点（即 v 的兄弟节点）
        // 如果 v 本身就是 A 值最小的那个子节点(arg1[u])，则需要搭配次小值 mn2[u]；否则搭配最小值 mn1[u]
        ll ex = (v == arg1[u]) ? mn2[u] : mn1[u];

        // 路径前缀和累加：加上父节点 u 的前缀和及当前一步的花费
        pre[v] = pre[u] + ex;

        dfs_pre(v, u); // 继续向下传递计算子树
    }
}

void solve()
{
    cin >> n >> m; // 读取节点数 n 和查询数 m

    // 重置并初始化各个数组大小
    c.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i)
    {
        cin >> c[i]; // 读取每个节点的购买费用
    }

    adj.assign(n + 1, vector<int>());
    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v); // 建立无向树边
        adj[v].push_back(u);
    }

    // 初始化各个动态规划与树信息数组
    parent_node.assign(n + 1, 0);
    tin.assign(n + 1, 0);
    tout.assign(n + 1, 0);
    timer_cnt = 0;

    A.assign(n + 1, 0);
    mn1.assign(n + 1, 0);
    mn2.assign(n + 1, 0);
    arg1.assign(n + 1, 0);
    pre.assign(n + 1, 0);

    // 1. 执行第一次 DFS，自底向上计算 A[u] 和子节点极值，并记录时间戳
    dfs_calc(1, 0);

    // 2. 执行第二次 DFS，自顶向下计算路径前缀和 pre[u]
    dfs_pre(1, 0);

    // 3. 循环回答 m 个查询
    while (m--)
    {
        int x, y;
        cin >> x >> y; // 输入起点 x 和目标点 y

        // 利用时间戳在 O(1) 时间内判断 y 是否为 x 的祖先
        if (tin[y] <= tin[x] && tout[x] <= tout[y])
        {
            // 如果 y 是 x 的祖先，路径花费直接利用前缀和相减得到：pre[x] - pre[y]
            cout << pre[x] - pre[y] << '\n';
        }
        else
        {
            // 如果 y 不是 x 的祖先，无法通过“向上合成”达到，输出 -1
            cout << -1 << '\n';
        }
    }
}

int main()
{
    // 开启 C++ 快速输入输出
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t)
    {
        while (t--)
        {
            solve(); // 处理每个测试用例
        }
    }
    return 0;
}