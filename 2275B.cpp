#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

#define endl '\n'
#define int long long
void solved(){
    int n;
    string s;
    cin>>n>>s;
    stack<int>stk;
    int k=0;
    vector<int>ans;
    map<int,int>mp;
    for(int i=0;i<n;i++){
        if(s[i]=='1'){
            stk.push(i);
        }else if(s[i]=='2'){
            if(!stk.empty()){
                mp[stk.top()]=1;
                stk.pop();
            }else{
                mp[i]=1;
            }
        }else{
            mp[i]=1;
        }
    }
    for(int i=0;i<n;i++){
        if(!mp[i]){
            ans.push_back(i+1);
        }
    }
    cout<<ans.size()<<endl;
    for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<" ";
    }
    cout<<"\n";
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
