#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
// #define int long long
#define lowbit(x) (x & -x)
struct BIT
{
    int n;
    vector<int> tree;
    BIT() : n(2000), tree(2001, 0) {}

    void add(int i, int delta)
    {
        for (; i <= 2000; i += i & -i)
            tree[i] += delta;
    }

    int query(int i)
    {
        int sum = 0;
        for (; i > 0; i -= i & -i)
            sum += tree[i];
        return sum;
    }

    int query_range(int l, int r)
    {
        if (l > r)
            return 0;
        return query(r) - query(l - 1);
    }
};
void solved(){
    int n;
    cin>>n;
    vector<int>a(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    BIT bit;
    int ans=0;
    for(int i=1;i<=n;i++){
        ans+=bit.query_range(a[i],2000);
        bit.add(a[i],1);
    }
    bool ok=ans%2;
    // cout<<ok<<endl;
    int m;
    cin>>m;
    while(m--){
        int l,r;
        cin>>l>>r;
        int cnt=r-l+1;
        int k=cnt*(cnt-1)/2;
        if(k&1)
        ok^=1;
        cout << (ok == 1 ? "odd\n" : "even\n");
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T=1;
    // cin>>T;
    while(T--){
       solved();
    }
    return 0;
}
