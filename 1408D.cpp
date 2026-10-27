#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
signed main(){
    int n,m;
    cin>>n>>m;
    vector<pair<int,int>>p(n),L(m);
    for(int i=0;i<n;i++){
        cin>>p[i].first>>p[i].second;
    }    
    for(int i=0;i<m;i++){
        cin>>L[i].first>>L[i].second;
    }
    vector<int>min_y(N,0);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(p[i].first<=L[j].first){
                int x=L[j].first-p[i].first;
                int y=L[j].second-p[i].second+1;
                min_y[x]=max(min_y[x],y);
            }
        }
    }
    for(int i=N-5;i>=0;i--){
        min_y[i]=max(min_y[i],min_y[i+1]);
    }
    int ans=1e9;
    for(int i=0;i<N;i++){
        ans=min(ans,i+min_y[i]);
    }
    cout<<ans<<endl;
}