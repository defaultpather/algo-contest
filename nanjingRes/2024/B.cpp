#include<bits/stdc++.h>
using namespace std;

#define int long long

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t=1;
    cin>>t;
    while(t--){
        string s;
        cin>>s;
        for(int i=0;i<s.size();i++){
            if(i&1){
                if(s[i]=='1'){
                    s[i]='0';
                }else if(s[i]=='0'){
                    s[i]='1';
                }
            }
        }
        stack<char>stk;
        for(int i=0;i<s.size();i++){
            if(!stk.empty()){
                if((stk.top()=='0'&&s[i]=='1')||(stk.top()=='1'&&s[i]=='0')){
                    stk.pop();
                    continue;
                }
            }
            stk.push(s[i]);
        }
        vector<int>a;
        while(!stk.empty()){
            a.push_back(stk.top()-'0');
            stk.pop();
        }
        reverse(a.begin(),a.end());
        int c0 = 0, c1 = 0;
        for(int i=0;i<a.size();i++){
            if(a[i]==2){
                if(c0<=c1){
                    a[i]=0;
                }else{
                    a[i]=1;
                }
            }
            c0+=a[i]==0?1:0;
            c1+=a[i];
        }
        stack<int> stk;
        for (int i = 0; i < a.size(); i++)
        {
            if (!stk.empty())
            {
                if ((stk.top() == 0 && a[i] == 1) || (stk.top() == 1 && a[i] == 0))
                {
                    stk.pop();
                    continue;
                }
            }
            stk.push(a[i]);
        }
        cout<<stk.size()<<"\n";
    }
}