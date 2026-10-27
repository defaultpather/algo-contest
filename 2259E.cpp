#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

#define endl '\n'
// #define int long long
const int INF=1e9+10;
void solved(){
    int n;
    cin>>n;
    vector<int>a(n+2);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    vector<int>diff(n+2,0);
    diff[1]=1;
    auto tag=[&](int l,int r){
        if(l<=r){
            diff[l]--;
            diff[r+1]++;  
        }
    };
    for(int i=1;i<=n;i++){
        if(a[i]!=-1){
            int d=a[i];
            tag(max(1,i-d+1),min(n,i+d-1));
        }
    }
    for(int i=1;i<=n;i++){
        diff[i]+=diff[i-1];
    }
    vector<int>c(n+2,0);
    int last=-INF;
    for(int i=1;i<=n;i++){
        if(diff[i]==1)last=i;
        c[i]=i-last;
    }
    last=INF;
    for(int i=n;i>=1;i--){
        if(diff[i]==1)last=i;
        c[i]=min(c[i],last-i);
    }
    for(int i=1;i<=n;i++){
        if(a[i]==-1)continue;
        if(a[i]!=c[i]){
            cout<<"-1\n";
            return;
        }
    }
    for(int i=1;i<=n;i++){
        if(diff[i]==1){
            cout<<1;
        }else{
            cout<<0;
        }
    }
    cout<<endl;
    /*
        0  1  1  0 1 1  0  1 2  3
        1  0  0  1 0 0  1  0 0  0 
    */
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
