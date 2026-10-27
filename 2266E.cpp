#include<bits/stdc++.h>
using namespace std;

#define int long long
const int MAXN=200010;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    vector<int>p(MAXN+1,0);
    for(int i=2;i<MAXN;i++){
        if(p[i]==0){
            for(int j=i;j<MAXN;j+=i){
                if(p[j]==0){
                    p[j]=i;
                }
            }
        }
    }

    int T=1;
    cin>>T;
    while(T--){
        int n,k;
        cin>>n>>k;
        vector<int>a(n);
        int mx=0;
        for(int i=0;i<n;i++){
            cin>>a[i];
            mx=max(mx,a[i]);
        }
        vector<int>g(mx+1,0);
        for(int x=k+1;x<=mx;x++){
            int best=LLONG_MAX;
            int v=x;
            while(v>1){
                int pp=p[v];
                best=min(best,pp*g[x/pp]);
                while(v%pp==0){
                    v/=pp;
                }
            }
            g[x]=best+1;
        }
        int ans=0;
        for(int i=0;i<n;i++){
            ans+=g[a[i]];
        }
        cout<<ans<<"\n";
    }
}