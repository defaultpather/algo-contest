#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

#define endl '\n'
#define int long long
void solved(){
    int x,y,r;
    cin>>x>>y>>r;
    int l=x-r-1,R=x+r+1,u=y+r+1,d=y-r-1;
    for(int i=l;i<=R;i++){
        for(int j=d;j<=u;j++){
            int res=abs(i-x)*abs(i-x)+abs(j-y)*abs(j-y);
            if(res==r*r){
                cout<<i<<" "<<j<<"\n";
                return;
            }
        }
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t=1;
    cin>>t;
    while(t--){
        solved();   
    }
    return 0;
}
