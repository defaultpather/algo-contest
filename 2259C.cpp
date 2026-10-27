#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

#define endl '\n'
#define int long long
void solved(){
    int n;
    cin>>n;
    vector<int>a(n+2);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    bool ok=1;
    for(int i=1;i<=n;i++){
        if(a[i]==-1&&ok){
            a[i]=1;
            break;
        }else if(a[i]==1&&ok){
            ok=0;
        }
    }
    ok=1;
    for(int i=n;i>0;i--){
        if(a[i]==-1&&ok){
            a[i]=1;
            break;
        }else if(a[i]==1&&ok){
            ok=0;            
        }
    }
    for(int i=1;i<=n;i++){
        if(a[i]==-1){
            cout<<0<<" ";
        }else{
            cout<<a[i]<<" ";
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
