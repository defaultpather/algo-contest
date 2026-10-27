#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

#define endl '\n'
#define int long long
void solved(){
    int n;
    cin>>n;
    vector<int>a(n);
    int odd=0,even=0;
    vector<int>p;
    for(int i=0;i<n;i++){
        cin>>a[i];
        if(a[i]&1){
            a[i]=1;
        }
        else{
            if(a[i]/2&1){
                a[i]=0;
            }else{
                a[i]=2;
            }
        }
    }
    array<int,3>cnt{};
    for(int i=0;i<n;i++){
        cnt[a[i]]++;
    }
    cout<<max({cnt[0],cnt[1],cnt[2]})<<endl;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin>>t;
    while(t--){
        solved();
    }
    return 0;
}
