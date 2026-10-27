#include<bits/stdc++.h>
using namespace std;

// #define int long long
#define debug(x) (cout<<#x<<" = "<<x<<'\n')

void solved(){
    int n;
    cin>>n;
    if(n>=97&&n<=122||n>=194&&n<=244||n>=291&&n<=366||n>=388){
        cout<<"Yes\n";
        int x=n/97;
        int y=n%97;
        string s="";
        if(y==0){
            s=string(x,'a');
        }else{  
            s=string(x,'a');
            int k=y/25;
            int ky=y%25;
            int sz=x-1;
            if(ky==0){
                for(int i=0;i<k;i++){
                    s[sz-i]='z';
                }
            }else{
                if(k==1){
                    s[sz-1]='z';
                    s[sz]='a'+ky;
                }else if(k==2){
                    s[sz-2]='z';
                    s[sz-1]='z';
                    s[sz]='a'+ky;
                }else if(k==3){
                    s[sz-3]='z';
                    s[sz-2]='z';
                    s[sz-1]='z';
                    s[sz]='a'+ky;
                }else if(k==0){
                    s[sz]='a'+ky;
                }
            }
        }
        cout<<s<<'\n';
    }else{
        cout<<"No\n";
    }
    if(n<97){
        cout<<"No\n";
        return;
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);//97~122
    int t=1;
    cin>>t;
    while(t--){
        solved();
    }
}