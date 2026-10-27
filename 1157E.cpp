#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long
struct DSU{
    vector<int>fa;
    DSU(int n){
        fa.resize(n);
        iota(fa.begin(),fa.end(),0);
    }
    int find(int u){
        return u==fa[u]?u:fa[u]=find(fa[u]);
    }
};
void solved(){
    int n;
    cin>>n;
    vector<int>a(n),cnt(n);
    for(int i=0;i<n;i++)cin>>a[i];
    for(int i=0;i<n;i++){
        int val;
        cin>>val;
        cnt[val]++;
    }
    DSU dsu(n);
    for(int i=0;i<n;i++){
        if(cnt[i]==0){
            dsu.fa[i]=(i+1)%n;
        }
    }
    for(int i=0;i<n;i++){
        int target=(n-a[i])%n;
        
        int cur=dsu.find(target);
        cout<<(a[i]+cur)%n<<" ";
        cnt[cur]--;
        if(cnt[cur]==0){
            dsu.fa[cur]=(cur+1)%n;
        }
    }
    cout<<endl;
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
