#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
#define int long long
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int l,r;
    cin>>l>>r;
    int x=l^r;
    if(x==0){
        cout<<0<<endl;
    }else{
        int h=0;
        for(int i=62;i>=0;i--){
            if(x>>i&1){
                h=i;
                break;
            }
        }
        cout<<(1ll<<(h+1))-1<<'\n';
    }
    return 0;
}
