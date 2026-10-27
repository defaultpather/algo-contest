#include<bits/stdc++.h>
using namespace std;

struct DSU{
    vector<int>fa,sz;
    DSU(int n){
        fa.resize(n);
        iota(fa.begin(),fa.end(),0);
        sz.assign(n,1);
    }
    int find(int u){
        return u==fa[u]?u:fa[u]=find(fa[u]);
    }
    bool merge(int u,int v){
        u=find(u);
        v=find(v);
        if(u==v){
            return false;
        }
        sz[u]+=sz[v];
        fa[v]=u;
        return true;
    }
    int size(int u){
        return sz[find(u)];
    }
};
const int N=2000010;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    cin>>n;
    string ans(N,'a');
    DSU dsu(N);
    int max_len=0;
    for(int i=0;i<n;i++){
        string t;
        int k;
        cin>>t>>k;
        int len=t.size();
        for(int j=0;j<k;j++){
            int st;
            cin>>st;
            max_len=max(max_len,st+len-1);//维护到达右侧的最长长度
            int end_pos=st+len-1;
            int cur=dsu.find(st);
            while(cur<=end_pos){
                ans[cur]=t[cur-st];
                dsu.fa[cur]=cur+1;
                cur=dsu.find(cur+1);
            }
        }
    }
    cout<<ans.substr(1,max_len)<<endl;
}