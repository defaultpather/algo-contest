#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

#define int long long

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin>>n;
    vector<int>a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    auto dfs=[&](this auto&& dfs,vector<int>p,int k)->int{
        if(k<0||p.size()==0)
            return 0;
        vector<int>p1,p2;
        for(int i=0;i<p.size();i++){
            if((1<<k)&p[i])
                p1.push_back(p[i]);
            else
                p2.push_back(p[i]);
        }
        if(p1.empty())return dfs(p2,k-1);
        else if(p2.empty())return dfs(p1,k-1);
        else return (1<<k)+min(dfs(p1,k-1),dfs(p2,k-1));
    };
    cout<<dfs(a,30)<<"\n";

    return 0;
}
