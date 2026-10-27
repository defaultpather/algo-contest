#include<bits/stdc++.h>
using namespace std;

#define int long long
void solved(){
    int n,k;
    cin>>n>>k;
    string s;
    cin>>s;
    string tar="nanjing";
    int pos=0,cnt=0;
    while((pos=s.find("nanjing",pos))!=string::npos){
        pos++;
        cnt++;
    }
    int x=s.find('g',0);
    if(x+1>k){
        cout<<cnt<<"\n";
    }else{
        string t1=s.substr(0,x+1);
        string t2=s.substr(x+1);
        string ans=t2+t1;
        // cout<<ans<<endl;
        int pos = 0, cnt = 0;
        while ((pos = ans.find("nanjing", pos)) != string::npos)
        {
            pos++;
            cnt++;
        }
        cout<<cnt<<"\n";
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