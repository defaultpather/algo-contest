#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
// #define int long long

struct LCA
{
    int n;
    vector<vector<int>> ver; // 邻接表存图：ver[u] 存储节点 u 的所有邻居
    vector<vector<int>> val; // 倍增表：val[x][i] 表示节点 x 向上跳 2^i 步到达的祖先节点
    vector<int> lg;          // 预处理 log2 数组：辅助快速获取跳跃步数
    vector<int> dep;         // 深度数组：dep[x] 表示节点 x 的深度（根节点深度为 1）

    LCA(int n)
    {
        this->n = n;
        ver.resize(n + 1);
        val.resize(n + 1, vector<int>(30)); // 30 足够应对 2^30 规模的深度（N <= 1e9）
        lg.resize(n + 1);                   // 1-base  lg[i]表示不超过i的最大的2的幂
        dep.resize(n + 1);

        // 预处理 lg 数组，lg[i] 等价于 floor(log2(i)) + 1    第一步最多可以安全的向上跳2^(lg[i]-1)步
        // 作用是便于后面做位运算和二进制跳跃时快速定位最大二进制位数
        for (int i = 1; i <= n; i++)
        {
            lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
        }
    }
    void add(int x, int y)
    {
        ver[x].push_back(y);
        ver[y].push_back(x);
    }
    // DFS 遍历树：维护节点深度并预处理倍增表 (val 数组)
    void dfs(int x, int fa)
    {
        val[x][0] = fa;       // x 向上跳 2^0 = 1 步就是父节点 fa
        dep[x] = dep[fa] + 1; // 深度递推

        // 递推倍增表：x 向上跳 2^i 步，相当于从 x 向上跳 2^(i-1) 步后再跳 2^(i-1) 步
        for (int i = 1; i <= lg[dep[x]]; i++) // 实际lg[dep[x]-1]就完全够了
        {
            val[x][i] = val[val[x][i - 1]][i - 1];
        }
        for (auto y : ver[x])
        {
            if (y == fa)
                continue;
            dfs(y, x);
        }
    }
    // 查询节点 x 和 y 的最近公共祖先 (LCA)
    int lca(int x, int y)
    {
        if (dep[x] < dep[y])
            swap(x, y);
        // 第二步：利用倍增将 x 提升到与 y 相同的深度
        while (dep[x] > dep[y])
        {
            // lg[dep[x] - dep[y]] - 1 对应当前深度差的最大二进制位 2^k
            x = val[x][lg[dep[x] - dep[y]] - 1];
        }
        // 如果提升后 x 和 y 重合，说明原 y 就是 x 的祖先，直接返回
        if (x == y)
            return x;

        // 第三步：x 和 y 一起同步向上跳跃
        // 从大到小尝试 2^k 步，寻找距离 LCA 最近的“下方临界点”
        for (int k = lg[dep[x]] - 1; k >= 0; k--)
        {
            if (val[x][k] == val[y][k])
                continue;  // 跳多了（到了 LCA 或 LCA 以上），不跳
            x = val[x][k]; // 还没到达 LCA，继续向上跳
            y = val[y][k];
        }
        // 循环结束后，x 和 y 刚好停在 LCA 的正下方一层，其父节点 val[x][0] 即为 LCA
        return val[x][0];
    }
    // 利用 LCA 计算 x 和 y 之间的树上距离
    int clac(int x, int y)
    {
        // 树上距离公式：dis(x, y) = dep[x] + dep[y] - 2 * dep[lca(x, y)]
        return dep[x] + dep[y] - 2 * dep[lca(x, y)];
    }
    // 外部调用的入口函数：传入根节点编号（默认 1），开启预处理
    void work(int root = 1)
    {
        dfs(root, 0);
    }
};
void solved(){
    int n,m;
    cin>>n>>m;
    LCA lca(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        lca.add(u,v);
    }
    lca.work(1);
    while(m--){
        int a,b,c;
        cin>>a>>b>>c;
        int h1=lca.lca(a,b),h2=lca.lca(a,c),h3=lca.lca(b,c);
        int high=h1!=h2?((lca.dep[h1]<lca.dep[h2])?h1:h2):h1;
        int low=h1!=h2?((lca.dep[h1]>lca.dep[h2])?h1:h2):h3;
        cout<<low<<" ";
        cout<<lca.dep[a]+lca.dep[b]+lca.dep[c]-lca.dep[high]*2-lca.dep[low]<<endl;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T=1;
    // cin>>T;
    while(T--){
       solved();
    }
    return 0;
}
