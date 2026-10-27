#include<bits/stdc++.h>
using namespace std;

#define int long long
const int INF=1e18;
const int N=2e5+10;
#define debug(x) (cout<<#x<<" = "<<x<<'\n')
void solved(){
    int n,m,k;
    cin>>n>>m>>k;
    vector<int>pos(n*m+1);
    for(int i=1;i<=n*m;i++){
        int p;
        cin>>p;
        pos[i]=(p+m-1)/m;
    }
    if(k>=m){
        cout<<m<<'\n';
        return;
    }
    map<int,int>cnt;
    for(int i=1;i<=n*m;i++){
        cnt[pos[i]]++;
        if(cnt[pos[i]]==m-k){
            cout<<max(m,i)<<"\n";
            return;
        }
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