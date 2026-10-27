#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const int mod=998244353;

#define int long long

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,k;
    cin>>n>>k;
    vector<int>a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    int sum=0;
    int tmpn=n,tmpk=k;
    set<int>s;
    while(tmpk--){
        sum+=tmpn;
        s.insert(tmpn);
        tmpn--;
    }
    cout<<sum<<" ";
    int lst=-1,ans=1,cnt=0;
    for(int i=0;i<n;i++){
        if(s.count(a[i])){
            if(lst==-1){
                ans=1;
            }else{
                ans=(ans*(i-lst))%mod;
            }
            lst=i;
            cnt=0;
            // cout<<"ans="<<ans<<'\n';
        }else{
            cnt++;
        }
    }
    // cout << "end_ans=" << ans << '\n';

    // if(lst!=n-1){
    //     ans*=(n-1-lst-1)%mod;
    // }
    cout<<ans%mod<<'\n';
    return 0;
}
