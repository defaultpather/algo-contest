#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N=200010;
int n,k,l,r;
struct node{
    int r,id;
    friend bool operator<(auto& x,auto& y){
        if(x.r==y.r)return x.id<y.id;
        return x.r<y.r;
    }
};
vector<node>a[N];//a[l]表示以l为左端点的线段的区间
set<node>st;//覆盖当前点i的线段信息
vector<int>ans;
void solved(){
    cin>>n>>k;
    node tmp;
    for(int i=0;i<n;i++){
        cin>>l>>r;
        tmp.r=r;tmp.id=i;
        a[l].push_back(tmp);
    }    
    for(int i=0;i<=200000;i++){
        while(st.size()&&((*st.begin()).r<i)){
            st.erase(*st.begin());
        }
        for(int j=0;j<a[i].size();j++){
            st.insert(a[i][j]);
        }
        while(st.size()>k){
            auto [r,id]=*st.rbegin();
            ans.push_back(id);
            st.erase(*st.rbegin());
        }
    }
    cout<<ans.size()<<endl;
    sort(ans.begin(),ans.end());
    for(int i=0;i<ans.size();i++){
        cout<<ans[i]+1<<" ";
    }
    cout<<endl;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T=1;
    // cin>>T;
    while(T--){
        solved();
    }
}