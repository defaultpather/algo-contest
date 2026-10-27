#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int N=600010;
const int MAXN=N*3;

int tree[MAXN][3];
bool is_end[MAXN];
int tree_cnt=1;
void insert(string& word){
    int cur=1;
    for(auto c:word){
        int path=c-'a';
        if(tree[cur][path]==0){
            tree[cur][path]=++tree_cnt;
        }
        cur=tree[cur][path];
    }
    is_end[cur]=true;
}
bool dfs(string &word, int pos, int cur, int rem)
{
    if (pos == word.length())
    {
        return rem == 0 && is_end[cur];
    }
    int path = word[pos] - 'a';

    if (tree[cur][path] != 0)
    {
        if (dfs(word, pos + 1, tree[cur][path], rem))
        {
            return true;
        }
    }
    if (rem > 0)
    {
        for (int next_path = 0; next_path < 3; next_path++)
        {
            if (next_path != path && tree[cur][next_path] != 0)
            {
                if (dfs(word, pos + 1, tree[cur][next_path], rem - 1))
                {
                    return true;
                }
            }
        }
    }
    return false;
}
void solved(){
    int n,m;
    cin>>n>>m;
    vector<string>s(n),t(m);
    for(int i=0;i<n;i++){   
        cin>>s[i];
        insert(s[i]);
    }
    for(int i=0;i<m;i++){
        cin>>t[i];
        bool ans=dfs(t[i],0,1,1);
        cout<<(ans?"YES\n":"NO\n");
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
