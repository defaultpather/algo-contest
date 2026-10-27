#include<bits/stdc++.h>
using namespace std;

#define int long long
#define debug(x) (cout<<#x<<" = "<<x<<'\n')
void solved(){
    string s;
    cin>>s;
    int n=s.size();
    bool ok=1;
    for(int i=n-1;i>=0;i--){
        if(s[i]=='-'&&(n-1-i+1)<=3){
            ok=0;
            break;
        }
    }
    if(s[0]!='>'||count(s.begin(),s.end(),'-')==0||!ok){
        cout<<"No\n";
        return;
    }
    int ed=0;
    for(int i=n-1;i>=0;i--){
        if(s[i]!='>'){
           ed=i;
           break;
        }
    }
    ed++;
    vector<int>l;
    for(int i=0;i<ed;i++){
        if(s[i]=='>'){
            l.push_back(i);
        }
    }   
    int z=l.back();
    while(l.size()<n){
        l.push_back(z);
    }
    vector<int>r;
    for(int i=n-1;i>=ed+2;i-=3){
        r.push_back(i);
    }
    z=ed+2;   
    while(r.size()<n){
        r.push_back(z);
    }
    cout<<"Yes "<<n<<"\n";
    for(int i=0;i<n;i++){
        cout<<l[i]+1<<" "<<r[i]-l[i]+1<<"\n";
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t=1;
    cin>>t;
    while(t--){
        solved();
    }
}