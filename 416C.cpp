#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
// #define int long long
void solved(){
    int n;
    cin>>n;
    priority_queue<array<int,3>>pq;
    for(int i=0;i<n;i++){
        int p,c;
        cin>>c>>p;
        pq.push({p,c,i+1});
    }
    int k;
    cin>>k;
    vector<pair<int,int>>r(k);
    for(int i=0;i<k;i++){
        cin>>r[i].first;
        r[i].second=i+1;
    }
    sort(r.begin(),r.end());
    vector<int>vis(k);
    int ans=0;
    vector<pair<int,int>>res;
    while(!pq.empty()){
        auto [p,c,o]=pq.top();
        pq.pop();
        for(int i=0;i<k;i++){
            if(c<=r[i].first&&vis[i]!=1){
                res.push_back({o,r[i].second});
                ans+=p;
                vis[i]=1;
                break;
            }
        }
    }
    cout<<res.size()<< " "<<ans<<"\n";
    for(auto v:res){
        cout<<v.first<< " "<<v.second<<"\n";
    }
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
