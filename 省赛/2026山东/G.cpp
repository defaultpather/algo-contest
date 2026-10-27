#include<bits/stdc++.h>
using namespace std;

#define int long long
const int INF=1e9;
void solved(){
    int n;
    cin>>n;
    multiset<pair<int,int>>ms;
    for(int i=0;i<n;i++){
        int a,b;
        cin>>a>>b;
        ms.insert({a,b});
    }
    int ans=0;
    while(!ms.empty()){
        auto [x,y]=*ms.begin();
        ms.erase(ms.begin());
        ans+=y;
        int bl=1;
        while(1){
            bl++;
            auto p=ms.lower_bound({x+1,INF});
            if(p==ms.begin())break;
            p=prev(p);
            auto [nxtx,nxty]=*p;
            if(nxtx!=x+1)break;
            ans+=nxty*bl;
            x=nxtx;
            ms.erase(p);
        }
    }
    cout<<ans<<"\n";
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