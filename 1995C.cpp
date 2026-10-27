#include <bits/stdc++.h>

using namespace std;
#define int long long

void solved(){
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int i=1;i<n;i++){
        if(a[i-1]>a[i]&&a[i]==1){
            cout<<"-1\n";
            return;
        }        
    }
    vector<int>ops(n);
    for(int i=1;i<n;i++){
        int x=a[i-1],y=a[i];
        int cnt=0;
        while(x!=1&&x*x<=y){//尽可能让cnt小
            x*=x;
            cnt--;
        }
        while(y<x){
            y*=y;
            cnt++;
        }
        ops[i]=max(0ll,ops[i-1]+cnt);
    }
    int sum=0,ans=0;
    for(int i=0;i<n;i++){
        sum+=ops[i];
    }
    cout<<sum<<endl;
}
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    cin >> t;
    while (t--){
        solved();
    }
}