#include<bits/stdc++.h>
using namespace std;

#define int long long

void solved(){
    int n;
    cin>>n;
    vector<int>s(n),t(n);
    for(int i=0;i<n;i++){
        cin>>s[i];
    }
    for(int i=0;i<n;i++){
        cin>>t[i];
    }
    sort(s.begin(),s.end());
    sort(t.begin(),t.end());
    if(s==t){
        cout<<"Yes\n";
        return;
    }
    bool fs=false,ft=false;
    for(int i=1;i<n;i++){
        fs|=(s[i-1]==s[i]-1);
        ft|=(t[i-1]==t[i]-1);
    }
    if(!(fs&&ft)){
        cout<<"No\n";
        return;
    }
    int cnts=0,cntt=0;
    for(int i=0;i<n;i++){
        cnts+=(s[i]&1);
        cntt+=(t[i]&1);
    }
    cout<<(cnts==cntt?"Yes\n":"No\n");
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