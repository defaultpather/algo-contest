#include<bits/stdc++.h>
using namespace std;

#define int long long

void solved(){
    int n,q;
    cin>>n>>q;
    vector<pair<int,int>>rag(q);
    for(int i=0;i<q;i++){
        cin>>rag[i].first>>rag[i].second;
    }
    sort(rag.begin(),rag.end(),[&](auto& x,auto& y){
        return x.second<y.second;
    });
    int lst=-1e9;
    int x=0;
    for(auto [l,r]:rag){
        if(l>lst){
            x++;
            lst=r;
        }
    }
    cout<<__lg(x)+1<<"\n";
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