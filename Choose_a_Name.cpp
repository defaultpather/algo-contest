#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int N=500010;
const int MAXN=N*27;

int tree[MAXN][26];
int pass[MAXN];    // 表示经过节点 i 的字符串数量
int end_cnt[MAXN]; // 表示以节点 i 结尾的字符串数量
int tree_cnt=1;

void insert(string &word)
{
    int cur = 1;
    pass[cur]++;
    for (char c : word)
    {
        int path = c - 'a';
        if (tree[cur][path] == 0)
        {
            tree[cur][path] = ++tree_cnt; // 前置++,因为是第二个结点
        }
        cur = tree[cur][path];
        pass[cur]++;
    }
    end_cnt[cur]++;
}
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
void clear()
{
    for (int i = 1; i <= tree_cnt; i++)
    {
        fill(tree[i], tree[i] + 26, 0);
        end_cnt[i] = 0;
        pass[i] = 0;
    }
}
void solved(){
    int n;
    cin>>n;
    vector<string>l(n),r(n);
    for(int i=0;i<n;i++){
        cin>>l[i]>>r[i];
    }    
    
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T=1;
    cin>>T;
    while(T--){
       solved();
    }
    return 0;
}

/*
    0  5  4  -1  -2 -3
    5  0  3  -2  -2 -3
    4  3  0  -1  -4 -2
   -1 -2  -1  0   7  6
   -2 -2  -4  7   0  5
   -3 -3  -2  6   5  0

*/