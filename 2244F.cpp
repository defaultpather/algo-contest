#include <bits/stdc++.h>
using namespace std;

// 全局结构体定义：用于存储提取出的子节点区间信息
struct seg
{
    int l;  // 子树权值的最小值
    int r;  // 子树权值的最大值
    int id; // 子节点在原始输入中的相对顺序（0, 1, 2, ...）

    // 重载 < 运算符，用于 std::sort 按区间左端点 l 升序排序
    friend bool operator<(seg a, seg b)
    {
        return a.l < b.l;
    }
};

// 全局变量与静态数组（避免动态内存开销）
vector<int> line[200000]; // 邻接表：line[u] 存储节点 u 的所有直接子节点编号
int a[200000];            // a[i]: 节点 i 的初始权值（0 表示未赋值/待填）
int l[200000];            // l[u]: 以 u 为根的子树中已知权值的最小值
int r[200000];            // r[u]: 以 u 为根的子树中已知权值的最大值
int flag;                 // 全局非法标记：1 表示不合法（输出 NO），0 表示合法（输出 YES）
int inf = 1000000000;     // 无穷大常量

vector<seg> v; // 临时容器：用于收集当前节点的所有直接子节点的区间信息

// 树上自底向上的 DFS 递归函数
void dfs(int t)
{
    int i, n = 0; // n 记录当前节点 t 的直接子节点数量，同时作为分配给子节点的原始 id
    seg sg;
    vector<int>::iterator it;

    // ----- 步骤 1：先递归处理所有子节点，并更新当前节点 t 的区间范围 [l[t], r[t]] -----
    for (it = line[t].begin(); it != line[t].end(); it++)
    {
        dfs(*it);                 // 后序遍历：先递归算出子节点 *it 的区间 [l[*it], r[*it]]
        l[t] = min(l[t], l[*it]); // 自底向上更新：父节点最小值 = 所有子节点最小值中的最小值
        r[t] = max(r[t], r[*it]); // 自底向上更新：父节点最大值 = 所有子节点最大值中的最大值
    }

    // ----- 步骤 2：收集所有子节点的区间 [l, r] 及原始相对位置 id -----
    for (it = line[t].begin(); it != line[t].end(); it++)
    {
        sg.l = l[*it];   // 获取子节点的最小值
        sg.r = r[*it];   // 获取子节点的最大值
        sg.id = n;       // 记录该子节点是第几个加入的（保存原始环形相对位置）
        n++;             // 子节点计数器自增
        v.push_back(sg); // 压入临时数组
    }

    // ----- 步骤 3：按区间左端点升序排序 -----
    sort(v.begin(), v.end());

    // ----- 步骤 4：核心校验（检查区间是否重叠 以及 环形顺序是否被破坏）-----
    for (i = 1; i < n; i++)
    {
        // 校验 1: v[i].l < v[i-1].r 表示相邻两个子树的权值区间发生了重叠/交叉，非法！
        // 校验 2: v[i].id != (v[i-1].id + 1) % n 表示按数值大小排序后，子节点打破了原有的环形相邻顺序，非法！
        if (v[i].l < v[i - 1].r || v[i].id != (v[i - 1].id + 1) % n)
            flag = 1; // 标记不合法
    }

    // ----- 步骤 5：清空临时容器，供下一个节点的 dfs 使用 -----
    v.clear();
}

int main()
{
    // 快速输入输出优化
    ios::sync_with_stdio(false), cin.tie(0);

    int T, n, p, i;
    for (cin >> T; T > 0; T--) // 处理 T 组测试数据
    {
        cin >> n; // 输入节点数

        // 构建树的邻接表（父节点 -> 子节点）
        for (i = 1; i < n; i++)
        {
            cin >> p;
            line[p - 1].push_back(i); // p-1 转为 0-based 索引，节点 i 是 p-1 的子节点
        }

        // 读入节点权值，并初始化每个节点的 [l[i], r[i]]
        for (i = 0; i < n; i++)
        {
            cin >> a[i];
            if (a[i]) // 若节点自带权值
            {
                l[i] = a[i]; // 初始区间为单点 [a[i], a[i]]
                r[i] = a[i];
            }
            else // 若节点权值为 0（代表空/未赋值）
            {
                l[i] = inf;  // 设为正无穷，方便被 min 更新
                r[i] = -inf; // 设为负无穷，方便被 max 更新
            }
        }

        flag = 0; // 重置全局非法标记为 0
        dfs(0);   // 从根节点 0 开始递归执行

        // 输出结果
        if (flag)
            cout << "NO\n";
        else
            cout << "YES\n";

        // 清空邻接表，准备下一组测试数据
        for (i = 0; i < n; i++)
            line[i].clear();
    }
    return 0;
}