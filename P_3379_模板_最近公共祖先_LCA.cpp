#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005; // 节点与询问的最大范围 N, M <= 500,000

// 1.1 树的邻接表表示：adj[u] 存放与节点 u 直接相连的所有邻居节点
vector<int> adj[MAXN];

struct Query
{
    int v;  // 目标节点
    int id; // 该询问的原始编号（以便最后按顺序输出）
};
// queries[u] 存放所有与节点 u 相关的离线查询
vector<Query> queries[MAXN];

int father[MAXN];   
bool visited[MAXN]; // visited[u] 为 true 表示 u 自身及其子树已 DFS 遍历完毕并回溯
int ans[MAXN];      // 存储第 id 个询问的最终 LCA 答案

int find(int u)
{
    if (father[u] == u)
        return u;
    return father[u] = find(father[u]); // 递归寻根 + 路径压缩
}

// =================【3. Tarjan 离线 LCA 核心遍历】=================
void tarjan(int u, int f)
{
    visited[u] = true;
    for (int v : adj[u])
    {
        if (v != f)
        {                  // 避免走回头路向父节点 f 倒退
            tarjan(v, u);  // 递归子树
            father[v] = u; // 【关键回溯点】：当 v 的整棵子树全部处理完毕后，将 v 合并到 u 所在集合
        }
    }

    // 【步骤 3】处理所有与当前节点 u 相关的离线询问
    for (const auto &q : queries[u])
    {
        int v = q.v;
        int id = q.id;

        // 如果另一个节点 v 之前已经被 DFS 彻底遍历过（即 visited[v] == true）
        // 那么此时 find(v) 返回的集合代表节点，恰好就是 u 和 v 的最近公共祖先 (LCA)
        if (visited[v])
        {
            ans[id] = find(v);
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, root;
    if (!(cin >> n >> m >> root))

    for (int i = 1; i <= n; i++)
    {
        father[i] = i;
    }
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v); 
        adj[v].push_back(u);
    }
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        // 离线查询必须双向存储：因为不知道 DFS 会先走到 u 还是先走到 v
        queries[u].push_back({v, i});
        queries[v].push_back({u, i});
    }

    // 从根节点 root 开始执行 Tarjan 算法
    tarjan(root, 0);

    // 依序输出每个询问的答案
    for (int i = 1; i <= m; i++)
    {
        cout << ans[i] << "\n";
    }

    return 0;
}