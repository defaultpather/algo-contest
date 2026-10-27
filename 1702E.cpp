#include<bits/stdc++.h>
using namespace std;

#define int long long
struct DSU
{
    vector<int> fa, siz;
    DSU() {}

    DSU(int n)
    {
        init(n);
    }

    void init(int n)
    {
        fa.resize(n);
        iota(fa.begin(), fa.end(), 0);
        siz.assign(n, 1);
    }

    int find(int u)
    {
        return u == fa[u] ? u : fa[u] = find(fa[u]);
    }

    bool same(int u, int v)
    {
        return find(u) == find(v);
    }

    bool merge(int u, int v)
    {
        u = find(u);
        v = find(v);
        if (u == v)
        {
            return siz[u]%2==0;
        }
        siz[u] += siz[v];
        fa[v] = u; // u为主
        return true;
    }

    int size(int u)
    {
        return siz[find(u)];
    }
};
void solved(){
    int n;
    cin>>n;
    vector<set<int>>a(n);
    for(int i=0;i<n;i++){
        int x,y;
        cin>>x>>y;
        x--,y--;
        a[x].insert(i);
        a[y].insert(i);
    }
    for(int i=0;i<n;i++){
        if(a[i].size()<2){
            cout<<"NO\n";
            return;
        }
    }
    DSU dsu(n);
    for(int i=0;i<n;i++){
        if(!dsu.merge(*a[i].begin(),*a[i].rbegin())){
            cout<<"NO\n";
            return;
        }
    }
    cout<<"YES\n";
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T=1;
    cin>>T;
    while(T--){
        solved();
    }
}