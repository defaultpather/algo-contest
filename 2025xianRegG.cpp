#include<bits/stdc++.h>
using namespace std;

#define int long long

void solved(){
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i=0;i<n;i++)cin>>a[i];
    sort(a.begin(),a.end());
    int s=0;
    for(int i=0;i<n;i++){
        if(s>=a[i])s++;
        else s--;
    }
    cout<<s<<" ";
    sort(a.begin(),a.end(),greater<int>());
    s=0;
    for(int i=0;i<n;i++){
        if(s>=a[i])s++;
        else s--;
    }
    cout<<s<<"\n";
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T=1;
    // cin>>T;
    while(T--){
        solved();
    }
}