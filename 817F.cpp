#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long
#include <bits/stdc++.h>
using namespace std;
// ---------------------- 珂朵莉树 (ODT) 模板 ----------------------
struct Node
{
    int l, r;
    mutable long long v; // mutable 允许在 set 内部直接修改 v
    // 按左端点 l 升序排列
    bool operator<(const Node &other) const
    {
        return l < other.l;
    }
};
struct ODT
{
    set<Node> s;
    int n;
    void init(int n, long long initial_val = 0)
    {
        this->n=n;
        s.clear();
        s.insert({1, n, initial_val});
    }
    // 作用：把包含位置 x 的节点 [l, r] 切分成 [l, x-1] 和 [x, r]
    // 返回：指向右半部分 [x, r] 节点的迭代器
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
    // 通用区间查询范例：求区间第 k 小 (以 CF896C 为例)
    long long kth(int l, int r, int k) {
        auto itr = split(r + 1);
        auto itl = split(l);

        vector<pair<long long, int>> vp; // {数值, 出现的频次(长度)}
        for (auto it = itl; it != itr; ++it) {
            vp.push_back({it->v, it->r - it->l + 1});
        }
        sort(vp.begin(), vp.end());
        for (const auto& p : vp) {
            k -= p.second;
            if (k <= 0) return p.first;
        }
        return -1LL;
    }
    int query(){
        for(auto it=s.begin();it!=s.end();it++){
            if(it->v==0){
                return it->l;
            }
        }
        return n+1;
    }
    void rev(int l,int r){
        auto itr=split(r+1);
        auto itl=split(l);
        for(auto it=itl;it!=itr;it++){
            if(it->v==0){
                it->v=1;
            }else{
                it->v=0;
            }
        }
    }
}odt;
void solved(){
    int n;
    cin>>n;
    odt.init(1e18+1);
    for(int i=0;i<n;i++){
        int t,l,r;
        cin>>t>>l>>r;
        if(t==1){
            odt.assign(l,r,1);
            cout<<odt.query()<<"\n";
        }else if(t==2){
            odt.assign(l,r,0);
            cout<<odt.query()<<"\n";
        }else{
            odt.rev(l,r);
            cout<<odt.query()<<"\n";
        }
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
