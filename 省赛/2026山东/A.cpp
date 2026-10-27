#include <bits/stdc++.h>
using namespace std;

int n, m;

// 返回 (i,j,第k层) 的节点编号；越界返回 0（0 用作"无效节点"）
int id(int i, int j, int k)
{
    if (!(1 <= i && i <= n && 1 <= j && j <= m && 0 <= k && k <= 4))
        return 0;
    return (i - 1) * m + j + k * n * m; // k=0 是格子，k=1..4 是四条链
}

const int N = 2.5e5 + 100; // 5 * (5e4) 上界
vector<int> E[N], G[N];    // E[v]=依赖v的节点；G[u]=u依赖的节点
int in[N];                 // 入度（拓扑排序用）
int ans[N];                // 每个格子的答案
bitset<5001> b[N];         // 分块：当前块 5000 个格子的闭包标记

// add(u,v)：v 必须先于 u 移除，即 u 依赖 v
void add(int u, int v)
{
    if (u && v) // 任一端越界(id=0)就忽略
    {
        E[v].push_back(u); // 边 v -> u
        G[u].push_back(v); // u 的依赖
        in[u]++;           // u 入度 +1
    }
}

bool ok[N]; // 该节点是否可移除（是否进了拓扑序）

void solv()
{
    cin >> n >> m;
    vector<vector<char>> a(n + 1, vector<char>(m + 1));

    // 清空上一组数据（节点数 = n*m*5）
    for (int i = 1; i <= n * m * 5; i++)
        E[i].clear(), in[i] = 0, ans[i] = 0, ok[i] = 0, G[i].clear();

    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        for (int j = 1; j <= m; j++)
            a[i][j] = s[j - 1];
    }

    // ---------- 建图 ----------
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            // 层节点依赖自己的格子：让链的闭包能"收集"沿途的格子
            for (int k = 1; k <= 4; k++)
                add(id(i, j, k), id(i, j, 0));

            // 四条链：layer(i,j) 依赖 layer(相邻格)，闭包沿方向延伸
            add(id(i, j, 1), id(i, j - 1, 1)); // 向左
            add(id(i, j, 2), id(i, j + 1, 2)); // 向右
            add(id(i, j, 3), id(i - 1, j, 3)); // 向上
            add(id(i, j, 4), id(i + 1, j, 4)); // 向下

            // 格子按箭头方向接到"前一格"的链上
            if (a[i][j] == 'U')
                add(id(i, j, 0), id(i - 1, j, 3));
            if (a[i][j] == 'D')
                add(id(i, j, 0), id(i + 1, j, 4));
            if (a[i][j] == 'L')
                add(id(i, j, 0), id(i, j - 1, 1));
            if (a[i][j] == 'R')
                add(id(i, j, 0), id(i, j + 1, 2));
        }
    }

    // ---------- 拓扑排序：找所有"可移除"节点 ----------
    queue<int> q;
    for (int i = 1; i <= n * m * 5; i++)
        if (!in[i]) // 入度 0 = 没有依赖
            q.push(i);

    vector<int> topo;
    topo.reserve(n * m * 5);

    while (q.size())
    {
        auto u = q.front();
        q.pop();
        topo.push_back(u);  // 依赖在前
        ok[u] = 1;          // u 可移除
        for (auto v : E[u]) // 释放依赖 u 的节点
            if ((--in[v]) == 0)
                q.push(v);
    }
    // 没进 topo 的节点：在环上或依赖环 → 不可移除

    // ---------- 按块计算每个格子的闭包大小 ----------
    for (int z = 1; z <= n * m; z += 5000) // 每块 5000 个格子
    {
        int l = z, r = min(n * m, z + 5000 - 1);

        // 按 topo 顺序（依赖在前）DP 闭包
        for (int i = 0; i < topo.size(); i++)
        {
            int u = topo[i];
            b[u].reset(); // 清空当前块的标记

            if (l <= u && u <= r) // u 自己是格子且在块内
                b[u][u - l] = 1;

            for (auto y : G[u]) // 并上所有依赖的闭包
                b[u] |= b[y];

            if (1 <= u && u <= n * m) // 只统计格子（层 0）的闭包大小
                ans[u] += b[u].count();
        }
    }

    // ---------- 输出 ----------
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (!ok[id(i, j, 0)]) // 不可移除
                ans[id(i, j, 0)] = -1;
            // cout << ans[id(i, j, 0)] << " ";
        }
        cout << '\n';
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
        solv();
}