#include<bits/stdc++.h>
using namespace std;

#define int long long

void solved(){
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    string s;
    cin>>s;
    int inv=0;
    int cnt1=0;
    for(int i=0;i<n;i++){
        cnt1+=a[i];
        if(a[i]==0){
            inv+=cnt1;
        }
    }
    cout<<inv<<" ";
    deque<int>dq;
    for(int i=0;i<n;i++){
        dq.push_back(a[i]);
    }
    int cnt0=count(a.begin(),a.end(),0);
    for(int i=0;i<n;i++){
        while(!dq.empty()&&dq.front()==0){
            dq.pop_front();
            cnt0--;
        }
        while(!dq.empty()&&dq.back()==1){
            dq.pop_back();
        }
        if(dq.empty()){
            cout<<0<<" ";
            continue;
        }
        if(s[i]=='1'){
            inv-=cnt0;
            dq.pop_front();
        }else{
            inv-=dq.size()-cnt0;
            cnt0--;
            dq.pop_back();
        }
        cout<<inv<<" ";
    }
    cout<<endl;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T=1;
    cin>>T;
    while(T--){
        solved();
    }
}