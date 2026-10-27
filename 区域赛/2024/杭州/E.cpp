#include<bits/stdc++.h>
using namespace std;

#define int long long
void solved(){
    int n,f;
    cin>>n>>f;
    vector<tuple<int,int,int>>a(n);
    int cnt=1;
    for(auto& [x,y,z]:a){
        cin>>x>>y;
        z=cnt++;
    }
    sort(a.begin(),a.end());
    for(int i=0;i<n;i++){
        cout<<get<2>(a[i])<<' ';
    }
    cout<<'\n';
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