#include <bits/stdc++.h>
using namespace std;
// #define int long long
const int N=200010;
const int MAXN=N*30;

int tree[MAXN][2];
int pass[MAXN];

int tree_cnt=1;

void insert(int val){
    int cur=1;
    pass[cur]++;
    for(int i=30;i>=0;i--){
        int path=val>>i&1;
        if(tree[cur][path]==0){
            tree[cur][path]=++tree_cnt;
        }
        cur=tree[cur][path];
        pass[cur]++;
    }
}
int search(int val)
{
    int cur = 1;
    for (int i=30;i>=0;i--)
    {
        int path = val>>i&1;
        if (tree[cur][path] == 0)
        {
            return 0;
        }
        cur = tree[cur][path];
    }
    return 1;
}
void deleteWord(int val)
{
    if (search(val) > 0)
    {
        int cur = 1;
        pass[cur]--;
        for (int i=30;i>=0;i--)
        {
            int path=val>>i&1;
            // 如果下一个节点的 pass 值减为 0，说明后面没有其他字符串依赖该分支，直接断开引用即可
            if (--pass[tree[cur][path]] == 0)
            {
                tree[cur][path] = 0;
                return;
            }
            cur = tree[cur][path];
        }
    }
}
int query(int val){
    int cur=1;
    int res=0;
    for(int i=30;i>=0;i--){
        int path=val>>i&1;
        int best_path=path^1;
        if(tree[cur][best_path]!=0){
            res|=(1<<i);
            cur=tree[cur][best_path];
        }else{
            cur=tree[cur][path];
        }
    }
    return res;
}
void solved(){
    int q;
    cin>>q;
    insert(0);
    while(q--){
        char type;
        int x;
        cin>>type>>x;
        if(type=='+'){
            insert(x);
        }else if(type=='-'){
            deleteWord(x);
        }else if(type=='?'){
            cout<<query(x)<<endl;
        }
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    int T=1;
    // cin>>T;
    while(T--){
       solved();
    }
    return 0;
}
