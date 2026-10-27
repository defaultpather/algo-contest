#include <bits/stdc++.h>
using namespace std;
const int N = 505;
vector<int> e[N];
int n, m, k, ans;
int vis[N], match[N]; 
bool dfs(int u)
{
    for (auto v : e[u])
    {
        if (vis[v])
            continue; 
        vis[v] = 1;   
        if (!match[v] || dfs(match[v]))
        {            
            match[v] = u; 
            return 1;     
        }
    }
    return 0; 
}
int main()
{
    cin >> n >> m >> k;
    for (int i = 0, a, b; i < k; i++)
        cin >> a >> b, e[a].push_back(b); 
    for (int i = 1; i <= n; i++)
    {
        memset(vis, 0, sizeof vis); 
        if (dfs(i))
            ans++; 
    }
    cout << ans;
}
