#include<bits/stdc++.h>
using namespace std;

#define int long long

void solved(){
    int n,x,y;
    cin>>n>>x>>y;
    vector<int>a(n+1);
    map<int,int>mp;
    int mx=0,mn=1e18;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        mp[a[i]]++;
        mx=max(mx,mp[a[i]]);
    }
    sort(a.begin()+1,a.end());
    mn=min(mn,(n-mx)*y);
    for(int i=1;i<=n;i++){
        mn=min(mn,a[i]*x+(n-i)*y);
    }
    cout<<mn<<endl;
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