#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 根据题目数据量大小调整 MAXN (最大节点总数)
const int MAXN = 150001;

// 静态数组实现前缀树
int tree[MAXN][26]; // 字典树节点，tree[i][path] 表示节点 i 沿着字符 path 走到的子节点编号
int pass[MAXN];     // 表示经过节点 i 的字符串数量
int end_cnt[MAXN];  // 表示以节点 i 结尾的字符串数量
int cnt;            // 节点编号计数器
// 初始化/建树
void build()
{
    cnt = 1;
}
// 插入字符串
void insert(const string &word)
{
    int cur = 1;
    pass[cur]++;
    for (char c : word)
    {
        int path = c - 'a';
        if (tree[cur][path] == 0)
        {
            tree[cur][path] = ++cnt;
        }
        cur = tree[cur][path];
        pass[cur]++;
    }
    end_cnt[cur]++;
}
// 查询字符串出现的次数 (原题要求判断是否存在，即 search > 0)
int search(const string &word)
{
    int cur = 1;
    for (char c : word)
    {
        int path = c - 'a';
        if (tree[cur][path] == 0)
        {
            return 0;
        }
        cur = tree[cur][path];
    }
    return end_cnt[cur];
}
// 查询以 pre 为前缀的字符串数量
int prefixNumber(const string &pre)
{
    int cur = 1;
    for (char c : pre)
    {
        int path = c - 'a';
        if (tree[cur][path] == 0)
        {
            return 0;
        }
        cur = tree[cur][path];
    }
    return pass[cur];
}
// 删除字符串
void deleteWord(const string &word)
{
    if (search(word) > 0)
    {
        int cur = 1;
        pass[cur]--;
        for (char c : word)
        {
            int path = c - 'a';
            // 如果下一个节点的 pass 值减为 0，说明后面没有其他字符串依赖该分支，直接断开引用即可
            if (--pass[tree[cur][path]] == 0)
            {
                tree[cur][path] = 0;
                return;
            }
            cur = tree[cur][path];
        }
        end_cnt[cur]--;
    }
}
// 多组数据清空前缀树
void clear()
{
    for (int i = 1; i <= cnt; i++)
    {
        fill(tree[i], tree[i] + 26, 0);
        end_cnt[i] = 0;
        pass[i] = 0;
    }
}

int main()
{
    // 开启 C++ 高效 IO，加速 cin / cout 读写
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    while (cin >> m)
    {
        build();
        int op;
        string word;
        for (int i = 0; i < m; i++)
        {
            cin >> op >> word;
            if (op == 1)
            {
                insert(word);
            }
            else if (op == 2)
            {
                deleteWord(word);
            }
            else if (op == 3)
            {
                cout << (search(word) > 0 ? "YES" : "NO") << "\n";
            }
            else if (op == 4)
            {
                cout << prefixNumber(word) << "\n";
            }
        }
        clear();
    }

    return 0;
}