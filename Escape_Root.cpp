#include <bits/stdc++.h>
using namespace std;

#define N 200005
map<int, int> id[N]; // id[u]：维护节点 u 子树传上来的幸存者，key为到达特征值，value为人的编号
int n, m, dep[N];    // 节点数、人数、节点深度数组
vector<int> adj[N];   // 树的邻接表

#define pii pair<int, int>
#define fi first
#define se second
#define mp make_pair
#define pb push_back

vector<pii> vec[N]; // vec[u]：记录在 u 点出发的人 (出发时间, 人员ID)
char ans[N];        // 最终输出的 01 答案字符串

void Dfs(int u, int fa)
{
    vector<int> del; // 局部变量，记录在节点 u 发生碰撞消亡的所有特征值 C

    for (auto v : adj[u])
    {
        if (v == fa)
            continue; // 避免向父节点反向遍历

        dep[v] = dep[u] + 1; // 计算子节点 v 的深度
        Dfs(v, u);           // 递归处理子树 v

        // 启发式合并 (Small-to-Large)：将小 map 合并入大 map，直接交换指针减少常数
        if (id[u].size() < id[v].size())
            swap(id[u], id[v]);

        // 将子节点 v 的 map 内容合并到当前节点 u 的map中
        for (auto v1 : id[v])
        {
            if (!v1.se)
                continue; // 已经被标记死亡的人（value为0）跳过不处理

            // v1.fi 是特征值 C，v1.se 是人员 ID
            // 若 u 的 map 中无此 C（或已置0），则此人顺利通过并继承到 u
            if (!id[u][v1.fi])
                id[u][v1.fi] = v1.se;
            else
                del.pb(v1.fi); // 否则说明该特征值 C 处发生碰撞，放入待销毁列表 del
        }
    }

    // 处理在当前节点 u 出发的人
    for (auto v : vec[u])
    {
        int s = v.fi + dep[u]; // 计算该人的到达特征值 C_i = s_i + dep[u]

        if (!id[u][s])
            id[u][s] = v.se; // 当前特征值无人占据，暂时存入 map
        else
            del.pb(s); // 与已有的人或之前碰撞的位置撞车，加入待销毁列表 del
    }

    // 统一清除在节点 u 发生碰撞的所有特征值，将其在 map 中归零，防止传给父节点
    for (auto v : del)
        id[u][v] = 0;
}

void slv()
{
    scanf("%d%d", &n, &m);

    // 建树（读入 n - 1 条无向边）
    for (int i = 1; i < n; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        adj[x].pb(y), adj[y].pb(x);
    }

    // 读入 m 个人的出发信息，默认所有人的答案先初始化为 '0'
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        vec[x].pb(mp(y, i)); // x: 出发节点, y: 出发时间 s_i, i: 人员编号
        ans[i] = '0';
    }

    Dfs(1, 0); // 从根节点 1 开始深搜

    // 搜索完成后，依然保存在根节点 id[1] 中的非零人员即为成功逃脱者
    for (auto v : id[1])
        if (v.se)
            ans[v.se] = '1';

    ans[m + 1] = 0;          // 字符串结尾符 '\0'
    printf("%s\n", ans + 1); // 从下标 1 开始打印 01 答案串
}

int main()
{
    slv();
    return 0;
}