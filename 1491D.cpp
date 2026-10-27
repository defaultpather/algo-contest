#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin>>q;
    while(q--){
        int u,v;
        cin>>u>>v;
        if(v<u){
            cout<<"NO\n";
            continue;
        }
        bool ok=1;
        int cu=0,cv=0;
        for(int i=0;i<=30;i++){
            if((1<<i)&u)cu++;
            if((1<<i)&v)cv++;
            if(cu<cv){
                ok=false;
                break;
            }
        }
        cout<<(ok?"YES":"NO")<<'\n';
    }


    return 0;
}
