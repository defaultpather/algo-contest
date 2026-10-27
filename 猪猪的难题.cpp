#include<bits/stdc++.h>
using namespace std;

#define int long long
void solved(){
    int n,q;
    cin>>n>>q;
    string s;
    cin>>s;
    s=' '+s;
    vector<vector<int>>pre(26,vector<int>(n+2,0));
    vector<vector<int>>suf(26,vector<int>(n+2,0));
    int d=0;
    for(int c=0;c<26;c++){
        char ch='a'+c;
        for(int i=1;i<=n;i++){
            pre[c][i]=pre[c][i-1];
            if(s[i]==ch)
                pre[c][i]=i;
        }
        for(int i=n;i>=1;i--){
            if(s[i]==ch)
                d=n-i+1;
            suf[c][i]=suf[c][i+1];
            suf[c][i]+=d;
        }
    }
    while(q--){
        int l,r;
        cin>>l>>r;
        int ans=0;
        for(int c=0;c<26;c++){
            int rr=pre[c][r];
            if(rr<l)continue;
            ans+=suf[c][l]-suf[c][rr+1];
            ans-=(rr-l+1)*(n-r);           
        }
        cout<<ans<<" \n"[q==0];
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