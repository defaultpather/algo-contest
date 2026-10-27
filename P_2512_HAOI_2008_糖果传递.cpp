#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

void solved(){
    int n;
    cin>>n;
    vector<int>a(n);
    int sum=0;
    for(int i=0;i<n;i++){
        cin>>a[i];
        sum+=a[i];
    }
    if(sum%n!=0){
        cout<<0<<endl;
        return;
    }
    int avg=sum/n;
    vector<int>c(n);
    c[0]=avg-a[0];
    for(int i=1;i<n;i++){
        c[i]=avg-a[i];
        c[i]+=c[i-1];
    }
    sort(c.begin(),c.end());
    int m=c.size();
    int mid=c[(m+1)/2-1];
    int ans=0;
    for(int i=0;i<n;i++){
        ans+=abs(c[i]-mid);
    }
    cout<<ans<<endl;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T=1;
    // cin>>T;
    while(T--){
       solved();
    }
    return 0;
}
