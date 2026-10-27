#include<bits/stdc++.h>
using namespace std;

#define int long long

void solved(){
    int n;
    cin>>n;
    vector<int>a(n),b(n),c(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
        a[i]--;
    }for(int i=0;i<n;i++){
        cin>>b[i];
        b[i]--;
    }for(int i=0;i<n;i++){
        cin>>c[i];
        c[i]--;
    }
    vector<int>mark(n);
    auto get=[&](auto p,auto q){
        vector<int>posQ(n);
        for(int i=0;i<n;i++){
            posQ[q[i]]=i;
        }
        int cur=0;
        for(int i=0;i<n;i++){
            cur=max(cur,posQ[p[i]]);
            if(cur==i){
                mark[cur]=1;
            }
        }
    };
    get(a,b);
    get(a,c);
    get(b,c);
    int ans=0;
    for(int i=0;i<n;i++){
        if(mark[i]){
            ans++;
        }
    }
    cout<<ans<<"\n";
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