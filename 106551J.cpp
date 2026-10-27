#include <bits/stdc++.h>
using namespace std;

// 针对 10^6 数据量的静态数组大小定义
const int MAXN = 1000005;
const int MAXTOT = 2000005; // 2 * MAXN
const int MAXV = 1000005;

// 快读与快写，保证 10^6 级别的 I/O 不拖后腿
namespace FastIO
{
    inline char read_char()
    {
        static char buf[1 << 20], *p1 = buf, *p2 = buf;
        return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++;
    }
    template <typename T>
    inline void read(T &x)
    {
        x = 0;
        char c = read_char();
        while (c < '0' || c > '9')
            c = read_char();
        while (c >= '0' && c <= '9')
        {
            x = x * 10 + (c - '0');
            c = read_char();
        }
    }
    inline void write_int(int x)
    {
        if (x == 0)
        {
            putchar('0');
            putchar('\n');
            return;
        }
        char buf[20];
        int len = 0;
        while (x > 0)
        {
            buf[len++] = x % 10 + '0';
            x /= 10;
        }
        while (len--)
            putchar(buf[len]);
        putchar('\n');
    }
}
using namespace FastIO;

int n, q;
int a[MAXN];
int first_pos[MAXV];

// 并查集数组
int dsu_fa[MAXTOT];
inline int dsu_find(int u)
{
    int r = u;
    while (r != dsu_fa[r])
        r = dsu_fa[r];
    int curr = u;
    while (curr != r)
    {
        int nxt = dsu_fa[curr];
        dsu_fa[curr] = r;
        curr = nxt;
    }
    return r;
}

// 静态化的 Kruskal 重构树结构
int tot;
int val[MAXTOT];
int lc[MAXTOT], rc[MAXTOT]; // 重构树左右孩子
int tree_par[MAXTOT];       // 树上的父节点
int dep[MAXTOT];            // 深度数组
int up[21][MAXTOT];         // 倍增表：up[k][u] 表示 u 向上跳 2^k 步

inline void add_kruskal_edge(int u, int v, int w)
{
    u = dsu_find(u);
    v = dsu_find(v);
    if (u != v)
    {
        tot++;
        val[tot] = w;
        lc[tot] = u;
        rc[tot] = v;

        dsu_fa[u] = tot;
        dsu_fa[v] = tot;
        dsu_fa[tot] = tot;

        tree_par[u] = tot;
        tree_par[v] = tot;
    }
}

// LCA 快捷查询
inline int query_lca(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    // 1. 提升 x 到与 y 同一深度
    for (int k = 20; k >= 0; k--)
    {
        if (dep[x] - (1 << k) >= dep[y])
        {
            x = up[k][x];
        }
    }
    if (x == y)
        return val[x];
    // 2. 同步向上跳寻找 LCA
    for (int k = 20; k >= 0; k--)
    {
        if (up[k][x] != up[k][y])
        {
            x = up[k][x];
            y = up[k][y];
        }
    }
    return val[up[0][x]];
}

int main()
{
    read(n);
    read(q);

    int max_val = 0;
    for (int i = 1; i <= n; i++)
    {
        read(a[i]);
        if (a[i] > max_val)
            max_val = a[i];
        if (first_pos[a[i]] == 0)
        {
            first_pos[a[i]] = i;
        }
    }

    // 初始化 DSU 根
    tot = n;
    for (int i = 1; i <= 2 * n; i++)
    {
        dsu_fa[i] = i;
    }

    // 1. 合并相同数值的点（边权直接为 a[i]）
    for (int i = 1; i <= n; i++)
    {
        int u = first_pos[a[i]];
        if (u != i)
        {
            add_kruskal_edge(u, i, a[i]);
        }
    }

    // 2. 调和级数倒序枚举 GCD 并合并
    for (int g = max_val; g >= 1; g--)
    {
        int first_node = 0;
        for (int mult = g; mult <= max_val; mult += g)
        {
            if (first_pos[mult] != 0)
            {
                int node = first_pos[mult];
                if (first_node == 0)
                {
                    first_node = node;
                }
                else
                {
                    if (dsu_find(first_node) != dsu_find(node))
                    {
                        add_kruskal_edge(first_node, node, g);
                    }
                }
            }
        }
    }

    // 3. 拓扑倒序递推深度 dep 和 up[0]（完全无递归，极速 $O(tot)$）
    for (int u = tot; u >= 1; u--)
    {
        if (tree_par[u] == 0)
        {
            dep[u] = 1;
        }
        int left = lc[u];
        int right = rc[u];
        if (left)
        {
            dep[left] = dep[u] + 1;
            up[0][left] = u;
        }
        if (right)
        {
            dep[right] = dep[u] + 1;
            up[0][right] = u;
        }
    }

    // 4. 构建倍增 LCA 表
    for (int k = 1; k <= 20; k++)
    {
        for (int i = 1; i <= tot; i++)
        {
            up[k][i] = up[k - 1][up[k - 1][i]];
        }
    }

    // 5. 处理询问
    while (q--)
    {
        int x, y;
        read(x);
        read(y);
        if (x == y)
        {
            write_int(a[x]);
        }
        else
        {
            write_int(query_lca(x, y));
        }
    }

    return 0;
}