#include <bits/stdc++.h>
using namespace std;

const int N = 200050, M = 200050;
int to[M * 2], ne[M * 2], h[N], idx;
int U[M], V[M]; 
void add(int a, int b)
{
    to[++idx] = b;
    ne[idx] = h[a];
    h[a] = idx;
}
int n, m, color[N];//0-未染色 1- 2-

bool dfs(int u, int c)
{
    color[u]=c;
    for(int i=h[u];i;i=ne[i]){
        int v=to[i];
        if(!color[v]){
            if(dfs(v,3-c)){
                return 1;
            }
        }else if(color[v]==c){
            return 1;
        }
    }
    return 0;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++){
        cin >> U[i] >> V[i];
        add(U[i], V[i]);
        add(V[i], U[i]);
    }
    bool ok = true;
    for (int i = 1; i <= n; i++){
        if (!color[i]){
            if (dfs(i, 1)){
                ok = false;
                break;
            }
        }
    }
    if (!ok){
        cout << "NO\n";
    }else{
        cout << "YES\n";
        for (int i = 1; i <= m; i++){
            if (color[U[i]] == 1)
                cout << '1';
            else
                cout << '0';
        }
        cout << "\n";
    }
}