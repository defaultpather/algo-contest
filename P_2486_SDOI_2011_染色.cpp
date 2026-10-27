#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100001; // 最大节点数
int n, m;                // n: 节点总数, m: 操作总数
int arr[MAXN];           // 存储每个节点的初始颜色

// 链式前向星存图
int head[MAXN];     // 每一个节点出发的第一条边的索引
int nxt[MAXN << 1]; // 同一节点出发的下一条边的索引 (双向边，需 2 倍空间)
int to[MAXN << 1];  // 边所指向的节点编号
int cntg = 0;       // 边的计数器

// 树链剖分（HLD）相关数组
int fa[MAXN];  // 节点的父节点
int dep[MAXN]; // 节点的深度
int siz[MAXN]; // 以当前节点为根的子树大小
int son[MAXN]; // 重儿子编号（子树最大的儿子节点）
int top[MAXN]; // 当前节点所在重链的链顶节点
int dfn[MAXN]; // 节点的 DFS 序（把树压成一维数组的索引）
int seg[MAXN]; // dfn 的反向映射：seg[dfn 序] = 原节点编号
int cntd = 0;  // DFS 序时间戳计数器

// 线段树相关数组（维护一维 DFS 序上的区间颜色段数）
int sum[MAXN << 2];    // 线段树节点维护的区间颜色段数
int lcolor[MAXN << 2]; // 当前线段树区间最左端节点的颜色
int rcolor[MAXN << 2]; // 当前线段树区间最右端节点的颜色
int change[MAXN << 2]; // 区间覆盖的懒标记（0 表示无标记，非 0 表示要覆盖的颜色）

// 链式前向星加边（无向边需调用两次）
void addEdge(int u, int v)
{
    nxt[++cntg] = head[u]; // 新边的下一条边指向 u 原来的头边
    to[cntg] = v;          // 新边的终点是 v
    head[u] = cntg;        // 更新 u 的头边为当前边
}

// 第一次 DFS：求出 fa, dep, siz, son
void dfs1(int u, int f)
{
    fa[u] = f;           // 记录父节点
    dep[u] = dep[f] + 1; // 记录深度
    siz[u] = 1;          // 初始化子树大小为 1（包含自身）

    // 遍历 u 的所有邻接点，递归求深度和父节点
    for (int e = head[u], v; e > 0; e = nxt[e])
    {
        v = to[e];
        if (v != f)
        {
            dfs1(v, u);
        }
    }

    // 再次遍历邻接点，统计子树大小并筛选出重儿子
    for (int e = head[u], v; e > 0; e = nxt[e])
    {
        v = to[e];
        if (v != f)
        {
            siz[u] += siz[v]; // 累加子树大小
            // 如果当前儿子子树更大，更新重儿子
            if (son[u] == 0 || siz[son[u]] < siz[v])
            {
                son[u] = v;
            }
        }
    }
}

// 第二次 DFS：剖分重链，生成 DFN 序
void dfs2(int u, int t)
{
    top[u] = t;      // 记录 u 所在重链的链顶
    dfn[u] = ++cntd; // 分配当前节点的 DFN 序
    seg[cntd] = u;   // 建立反向映射：记录该 DFN 序对应原树上的哪个节点

    if (son[u] == 0)
    { // 叶子节点（没有重儿子），直接返回
        return;
    }
    dfs2(son[u], t); // 优先递归重儿子，保证同一条重链上的 DFN 序连续

    // 递归轻儿子，轻儿子会作为新重链的链顶
    for (int e = head[u], v; e > 0; e = nxt[e])
    {
        v = to[e];
        if (v != fa[u] && v != son[u])
        {
            dfs2(v, v); // 轻儿子的链顶就是它自己
        }
    }
}

// 线段树向上更新（PushUp）：合并左右子树的颜色段数信息
void up(int i)
{
    // 基础段数 = 左子树段数 + 右子树段数
    sum[i] = sum[i << 1] + sum[i << 1 | 1];

    // 关键点：如果左子树的最右侧颜色 == 右子树的最左侧颜色，说明颜色连通，总段数减 1
    if (rcolor[i << 1] == lcolor[i << 1 | 1])
    {
        sum[i]--;
    }

    // 更新当前区间的左右边界颜色
    lcolor[i] = lcolor[i << 1];
    rcolor[i] = rcolor[i << 1 | 1];
}

// 线段树节点施加覆盖懒标记
void lazy(int i, int v){
    sum[i] = 1;    // 区间整体被染成同一种颜色，颜色段数必为 1
    lcolor[i] = v; // 最左颜色变为 v
    rcolor[i] = v; // 最右颜色变为 v
    change[i] = v; // 记录懒标记值
}

// 线段树向下传递懒标记（PushDown）
void down(int i)
{
    if (change[i] != 0)
    {                                // 如果存在待下传的染色标记
        lazy(i << 1, change[i]);     // 下传给左儿子
        lazy(i << 1 | 1, change[i]); // 下传给右儿子
        change[i] = 0;               // 清除当前节点的标记
    }
}

// 建树：初始化 DFS 序对应的一维线段树
void build(int l, int r, int i){
    if (l == r)
    {                            // 叶子节点
        sum[i] = 1;              // 单点颜色段数为 1
        lcolor[i] = arr[seg[l]]; // 获取原树节点 seg[l] 的初始颜色
        rcolor[i] = arr[seg[l]];
    }
    else
    {
        int mid = (l + r) / 2;
        build(l, mid, i << 1);         // 建左子树
        build(mid + 1, r, i << 1 | 1); // 建右子树
        up(i);                         // 向上合并
    }
}

// 线段树区间修改：将 DFN 区间 [jobl, jobr] 覆盖染色为 jobv
void update(int jobl, int jobr, int jobv, int l, int r, int i)
{
    if (jobl <= l && r <= jobr)
    {                  // 当前线段树区间被完全包含
        lazy(i, jobv); // 打上懒标记并更新
    }
    else
    {
        down(i); // 下传标记
        int mid = (l + r) / 2;
        if (jobl <= mid)
        {
            update(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid)
        {
            update(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i); // 重新合并信息
    }
}

// 线段树区间查询：查询 DFN 区间 [jobl, jobr] 内的颜色段数
int query(int jobl, int jobr, int l, int r, int i)
{
    if (jobl <= l && r <= jobr)
    {
        return sum[i]; // 当前区间被完全覆盖，直接返回段数
    }
    down(i); // 下传标记
    int mid = (l + r) / 2;
    if (jobr <= mid)
    { // 全在左子树
        return query(jobl, jobr, l, mid, i << 1);
    }
    else if (jobl > mid)
    { // 全在右子树
        return query(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    else
    { // 跨越左右子树
        int ans = query(jobl, jobr, l, mid, i << 1) + query(jobl, jobr, mid + 1, r, i << 1 | 1);
        // 比对中点两侧边界颜色：若左子树最右与右子树最左相同，答案 -1
        if (rcolor[i << 1] == lcolor[i << 1 | 1])
        {
            ans--;
        }
        return ans;
    }
}

// 单点查询：获取 DFN 序号为 jobi 的节点当前颜色
int pointColor(int jobi, int l, int r, int i)
{
    if (l == r)
    {
        return lcolor[i];
    }
    down(i); // 必须下传标记，确保拿到的单点颜色是最新的
    int mid = (l + r) / 2;
    if (jobi <= mid)
    {
        return pointColor(jobi, l, mid, i << 1);
    }
    else
    {
        return pointColor(jobi, mid + 1, r, i << 1 | 1);
    }
}

// 树剖路径修改：将树上路径 x 到 y 的所有节点染成颜色 v
void pathUpdate(int x, int y, int v)
{
    while (top[x] != top[y])
    { 
        if (dep[top[x]] <= dep[top[y]])
        {
            update(dfn[top[y]], dfn[y], v, 1, n, 1); 
            y = fa[top[y]];                          // y 跳到链顶的父节点
        }
        else
        {
            update(dfn[top[x]], dfn[x], v, 1, n, 1); // 修改 top[x] -> x 这段区间
            x = fa[top[x]];                          // x 跳到链顶的父节点
        }
    }
    // 处理最后同一条重链上的区间 [LCA, 较低节点]
    update(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]), v, 1, n, 1);
}

// 树剖路径查询：查询树上路径 x 到 y 的颜色段数
int pathColors(int x, int y)
{
    int ans = 0, sonc, fac;
    while (top[x] != top[y])
    { // x 和 y 不在同一条重链时循环
        if (dep[top[x]] <= dep[top[y]])
        {
            ans += query(dfn[top[y]], dfn[y], 1, n, 1); // 累加当前重链段内的颜色段数

            // 单点查询跨链处的颜色：
            sonc = pointColor(dfn[top[y]], 1, n, 1);    // 链顶节点的颜色
            fac = pointColor(dfn[fa[top[y]]], 1, n, 1); // 链顶父节点的颜色
            y = fa[top[y]];                             // 跳至上一条链
        }
        else
        {
            ans += query(dfn[top[x]], dfn[x], 1, n, 1);
            sonc = pointColor(dfn[top[x]], 1, n, 1);
            fac = pointColor(dfn[fa[top[x]]], 1, n, 1);
            x = fa[top[x]];
        }
        // 如果跳过轻边时，链顶节点与父节点颜色相同，说明段数多算了一次，需 -1
        if (sonc == fac)
        {
            ans--;
        }
    }
    // 加上最后同一条重链上的颜色段数
    ans += query(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]), 1, n, 1);
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i]; // 读入节点初始颜色
    }

    // 读入 n - 1 条无向边
    for (int i = 1, u, v; i < n; i++)
    {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }

    dfs1(1, 0);     // 第一次 DFS，根节点设为 1，父节点为 0
    dfs2(1, 1);     // 第二次 DFS，根节点设为 1，初始链顶设为 1
    build(1, n, 1); // 建立线段树

    string op;
    int x, y;
    for (int i = 1; i <= m; i++)
    {
        cin >> op;
        cin >> x >> y;
        if (op == "C")
        { // 染色操作
            int z;
            cin >> z;
            pathUpdate(x, y, z);
        }
        else
        { // 查询操作
            cout << pathColors(x, y) << "\n";
        }
    }
    return 0;
}