#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
#define int long long
void solved(){
    int n,m,k;
    cin>>n>>k>>m;
    string s;
    cin>>s;
    int now=n-k;
    int rem=k;
    int mag=0;
    for(int i=0;i<m;i++){
        if(s[i]=='0'){
            rem=min(n,rem+1);
            now=max(0ll,now-1);
        }else{
            if(rem>0){
                rem=max(0ll,rem-1);
                now=min(n,now+1);
            }else{
                mag++;
            }
        }
    }
    cout<<mag<<"\n";
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
