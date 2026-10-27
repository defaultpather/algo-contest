#include<bits/stdc++.h>
using namespace std;

#define int long long

void solved(){
    int n;
    cin>>n;
    if(n&1){
        cout<<"No\n";
    }else{
        cout<<"Yes\n";
        cout<<n/2<<" "<<n/2<<"\n";
    }
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