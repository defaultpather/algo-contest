#include<bits/stdc++.h>
using namespace std;

#define int long long
const int INF=1e9;
void solved(){
    int n,m;
    cin>>n>>m;
    if(n*m==3||n*m==4){
        cout<<"No\n";
        return;
    }
    if(n==2&&m==3){
        cout<<"Yes\n";
        cout<<"0 4 2\n3 1 5\n";
        return;
    }
    const int INF=1e9;
    vector<vector<int>>adj(n+1,vector<int>(m+1,INF));
    int cnt=0;
    for(int i=1;i<=n;i++){
        for(int j=((i&1)?2:1);j<=m;j+=2){
            adj[i][j]=cnt++;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(adj[i][j]==INF){
                adj[i][j]=cnt++;
            }
        }
    }
    cout<<"Yes\n";
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cout<<adj[i][j]<<" ";
        }
        cout<<'\n';
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



/* 
        2,4
    3,3 3,4
4,2 4,3 4,4


    1,3
2,2 2,3
*/