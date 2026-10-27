#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
void solved(){
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i=0;i<n;i++)cin>>a[i];
    int sum=accumulate(a.begin(),a.end(),0);
    int mx=*max_element(a.begin(),a.end());
    if(mx>sum/2)cout<<"T"<<'\n';
    else
        cout<<(sum&1?"T":"HL")<<'\n';
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t=1;
    cin>>t;
    while(t--)solved();
    return 0;
}
