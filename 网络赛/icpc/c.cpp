#include<bits/stdc++.h>
using namespace std;

#define int long long

void solved(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>>adj(n);
    vector<int>deg(n);//indegree
    for(int i=0;i<m;i++){
        int l,r;
        cin>>l>>r;
        l--,r--;
        int lst=-1;
        for(int j=l;j<=r;j++){
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
    priority_queue<int,vector<int>,greater<int>>pq;
    for(int i=0;i<n;i++){//这一步已经把远点加入了
        if(!deg[i]){
            pq.push(i);
        }
    }
    vector<int>p(n);
    for(int i=0;i<n;i++){
        if(pq.empty()){
            cout<<"-1\n";
            return;
        }   
        auto x=pq.top();
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
    int t=1;
    cin>>t;
    while(t--){
        solved();
    }
}