#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

#define endl '\n'
#define int long long
void solved(){
    int n;
    cin>>n;
    string s;
    cin>>s;
    int mx=0;
    int cnt=-1;
    for(int i=0,j=0;i<n;i++){
        int lst=i;
        while(i<n&&s[i]=='#'){
            i++;
        }
        mx=max(mx,i-lst);
    }
    cout<<(mx+1)/2<<endl;
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
