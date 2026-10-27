#include<bits/stdc++.h>
using namespace std;

#define int long long
const int  INF=1e9;
void solved(){
    int n;
    cin>>n;
    vector<int>a(n);
    vector<int>odd,even;
    for(int i=0;i<n;i++){
        cin>>a[i];
        if(a[i]&1){
            odd.push_back(a[i]);
        }else{
            even.push_back(a[i]);
        }
    }
    int odd_min=INF;
    int odd_max=-INF;
    int even_min=INF;
    int even_max=-INF;
    if(!odd.empty()){
        for(auto v:odd){
            odd_min=min(odd_min,v);
            odd_max=max(odd_max,v);
        }
    }
    if(!even.empty()){
        for(auto v:even){
            even_min=min(even_min,v);
            even_max=max(even_max,v);
        }
    }
    bool ok=1;
    if(!even.empty()){
        int mx=even[0];
        for(int i=1;i<even.size();i++){
            if(mx>even[i]){//说明有逆序对
                if(odd_min>even[i]&&odd_max<mx){
                    ok=0;
                    break;
                }
            }else{
                mx=even[i];
            }
        }
    }
    if(!odd.empty()){
        int mx=odd[0];
        for(int i=1;i<odd.size();i++){
            if(mx>odd[i]){
                if(even_min>odd[i]&&even_max<mx){
                    ok=0;
                    break;
                }
            }else{
                mx=odd[i];
            }
        }
    }
    if(ok){
        cout<<"YES\n";
    }else{
        cout<<"NO\n";
    }
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