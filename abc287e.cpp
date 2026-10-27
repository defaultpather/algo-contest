#include <bits/stdc++.h>
using namespace std;
using i64 = long long;//constexpr 0LL
using pii = pair<int, int>; 
#define endl '\n'
#define xx first
#define yy second
#define debug(x) (cout << "@ " << #x << " = " << x << endl)
constexpr i64 linf = 1e18;
constexpr int inf = 1e9;
constexpr int MOD = 1e9+7;
constexpr int N = 2e5 + 10;
// 根据题目数据量大小调整 MAXN (最大节点总数)
const int MAXN = 500010;
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

void solved(){
    int n;
    cin>>n;
    vector<string>s(n);
    for(int i=0;i<n;i++){
        cin>>s[i];
        insert(s[i]);
    }
    for (int i = 0; i < n; i++)
    {
        int cur = 1;
        int max_lcp = 0;

        // 直接沿着 s[i] 的字符在 Trie 上走，无需截取字符串
        for (int j = 0; j <s[i].size(); j++)
        {
            int path = s[i][j] - 'a';
            cur = tree[cur][path];
            if (pass[cur] >= 2)
                max_lcp = j + 1; 
            else
                break;
        }
        cout << max_lcp << "\n";
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    int T=1;
    build();
    // cin>>T;
    while(T--){
       solved();
    }
    return 0;
}
