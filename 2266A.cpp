#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

#define endl '\n'
#define int long long
void solved(){
    int n;
    cin>>n;
    vector<int>a(3);
    int mn=1e9;
    for(int i=0;i<3;i++){
        cin>>a[i];
        mn=min(mn,a[i]);
    }
    cout<<n-mn<<endl;
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
