#include<bits/stdc++.h>
using namespace std;

#define int long long

void solved(){
    int n;
    cin>>n;
    int ans=0;
    stack<int>stk;
    vector<char>op(n);
    vector<int>x(n);
    for(int i=0;i<n;i++){
        cin>>op[i]>>x[i];
        if(la.count(x[i]))nx[la[x[i]]]=op[i];
        la[x[i]]=i;
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