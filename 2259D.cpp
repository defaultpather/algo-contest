#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

#define endl '\n'
#define int long long
void solved(){
    int n;
    cin>>n;
    vector<int>a(n);
    map<int,int>mp;
    for(int i=0;i<n;i++){
        cin>>a[i];
        mp[a[i]]++;
    }
    if(mp[0]==1){    
        cout<<"NO\n";
        return;
    }
    cout<<"YES\n";
    int ok=0;
    for(int i=0;i<n;i++){
        if(!ok&&a[i]==0){
            cout<<"A";
            ok=1;
        }else if(a[i]==0&&ok){
            cout<<"C";
        }else{
            cout<<"B";
        }
    }
    cout<<endl;
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
