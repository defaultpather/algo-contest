#include<bits/stdc++.h>
using namespace std;

#define int long long

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    vector<int>a(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    set<int>s;
    for(int i=2;i<=n;i++){
        int x=a[i-1],y=a[i];
        s.insert(0);
        s.insert(x);
        s.insert(y);
        s.insert(x^y);
        s.insert(x|y);
        s.insert(x&y);
        s.insert(x&(x^y));
        s.insert(y&(x^y));
        s.insert(x^(x&y));
        s.insert(y^(x&y));
    }
    cout<<s.size()<<'\n';
}