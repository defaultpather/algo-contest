#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

void solved(){
    int n;
    cin>>n;
    vector<int>a(n);
    priority_queue<int,vector<int>,greater<int>>pq;
    int s1=0,s2=0,cnt=0;
    for(int i=0;i<n;i++){
        cin>>a[i];
        if(a[i]>=0){
            s1+=a[i];
            cnt++;
        }else{
            s2+=a[i];
            pq.push(a[i]);
            while(abs(s2)>s1&&!pq.empty()){
                s2-=pq.top();
                pq.pop();
            }
        }
    }
    cout<<cnt+pq.size()<<endl;
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
