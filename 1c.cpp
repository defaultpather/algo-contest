#include<bits/stdc++.h>
using namespace std;

#define int long long

void solved(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>>adj(n);
    vector<int>deg(n);
    for(int i=0;i<m;i++){
        int l,r;
        cin>>l>>r;
        l--;
        int lst=-1;
        for(int j=l;j<r;j++){
            int x;
            cin>>x;
            x--;
            if(j>l){
                adj[lst].push_back(x);
                deg[x]++;
            }
            lst=x;
        }
    }
    priority_queue<int,vector<int>,greater<>>pq;
    for(int i=0;i<n;i++){
        if(!deg[i]){
            pq.push(i);
        }
    }
    vector<int>p(n);
    for(int i=0;i<n;i++){
        if(pq.empty()){
            cout<<"-1\n";return;
        }
        int x=pq.top();
        pq.pop();
        p[x]=i+1;
        for(auto v:adj[x]){
            if(!--deg[v]){
                pq.push(v);
            }
        }
    }
    for(int i=0;i<n;i++){
        cout<<p[i]<<" \n"[i==n-1];
    }
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