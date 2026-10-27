#include<bits/stdc++.h>
using namespace std;

#define int long long
void solved(){
    int n,m,k;
    cin>>n>>m>>k;
    vector<int>fr(k+1);
    for(int i=0;i<n;i++){
        int f;
        cin>>f;
        fr[f]=1;
    }
    int base=0;
    vector<int>c(k+1);
    map<int,int>mp;
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        if(a==b){
            if(fr[a])base++;
            else c[a]++;
        }else if(fr[a]&&fr[b]){
            base++;
        }else if(fr[a]&&!fr[b]){
            c[b]++;
        }else if(!fr[a]&&fr[b]){
            c[a]++;
        }else{
            int u=min(a,b),v=max(a,b);
            mp[u*(k+1)+v]++;
        }
    }
    int best1=0,best2=0;
    for(int i=1;i<=k;i++){
        if(fr[i])continue;
        int val=c[i];
        if(val>best1){
            best2=best1;
            best1=val;
        }else if(val>best2){
            best2=val;
        }
    }
    int ans=base+best1+best2;
    for(auto [key,cnt]:mp){
        int u=key/(k+1);
        int v=key%(k+1);
        ans=max(ans,base+c[u]+c[v]+cnt);
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