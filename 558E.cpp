#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long
string ss;
int n,q;
array<int,26>cnt{};
struct Node
{
    int l, r;
    mutable long long v; // mutable 允许在 set 内部直接修改 v
    bool operator<(const Node &other) const
    {
        return l < other.l;
    }
};
struct ODT
{
    set<Node> s; // 每次assign都将他分成更多小块
    void init(int n, long long initial_val = 0)
    { // 将区间分成了多个用set维护的东西
        s.clear();
        s.insert({1, n, initial_val});
    }
    auto split(int x)
    {
        auto it = s.lower_bound({x, 0, 0});
        if (it != s.end() && it->l == x)
            return it;
        --it;
        if (it->r < x)
            return s.end(); // x 超出上界

        int l = it->l, r = it->r;
        long long v = it->v;

        s.erase(it);
        s.insert({l, x - 1, v});
        return s.insert({x, r, v}).first;
    }
    // 作用：把区间 [l, r] 彻底推平赋值为 val
    void assign(int l, int r, long long val)
    {
        auto itr = split(r + 1);
        auto itl = split(l);
        s.erase(itl, itr);
        s.insert({l, r, val});
    }
    void sort(int l,int r,int k){
        auto itr=split(r+1);
        auto itl=split(l);
        for(auto it=itl;it!=itr;it++){
            cnt[it->v]+=it->r-it->l+1;
        }
        int cur=l;
        if(k==0){
            for(int i=25;i>=0;i--){
                if(cnt[i]){
                    assign(cur,cur+cnt[i]-1,i);
                    cur=cur+cnt[i];
                }
            }
        }else{
            for(int i=0;i<26;i++){
                if(cnt[i]){
                    assign(cur,cur+cnt[i]-1,i);
                    cur=cur+cnt[i];
                }
            }
        }
        fill(cnt.begin(),cnt.end(),0);
    }
    void print(int l,int r){
        auto itr=split(r+1);
        auto itl=split(l);
        for(auto it=itl;it!=itr;it++){
            cout<<string(it->r-it->l+1,(char)('a'+it->v));
        }
        cout<<"\n";
    }
}odt;
void solved(){
    cin>>n>>q;
    cin>>ss;
    ss=" "+ss;
    for(int i=1;i<=n;i++){
        odt.s.insert({i,i,ss[i]-'a'});
    }
    while(q--){
        int i,j,k;
        cin>>i>>j>>k;
        odt.sort(i,j,k);
    }
    odt.print(1,n);
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
