#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long
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
    set<Node> s;
    // 初始化：清空并放入覆盖全图 [1, n] 的初始大节点
    void init(int n, long long initial_val = 0)
    {
        s.clear();
        s.insert({1, n, initial_val});
    }

    // 核心函数 1：split(x)
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
    // 核心函数 2：assign(l, r, val)
    // 作用：把区间 [l, r] 彻底推平赋值为 val
    void assign(int l, int r, long long val)
    {
        // ⚠️细节：必须先 split(r + 1)，再 split(l)！
        // 顺序颠倒可能会导致 itl 迭代器因为 erase/insert 重新平衡而失效 (野指针)
        auto itr = split(r + 1);
        auto itl = split(l);

        s.erase(itl, itr);     // 抹掉中间所有碎片节点
        s.insert({l, r, val}); // 插入推平后的全新大节点
    }
    // 通用区间修改范例：区间加 (Add)
    void add(int l, int r, long long val)
    {
        auto itr = split(r + 1);
        auto itl = split(l);

        for (auto it = itl; it != itr; ++it)
        {
            it->v += val; // 利用 mutable 关键字修改
        }
    }
    // 通用区间查询范例：求区间第 k 小 (以 CF896C 为例)
    long long kth(int l, int r, int k)
    {
        auto itr = split(r + 1);
        auto itl = split(l);

        vector<pair<long long, int>> vp; // {数值, 出现的频次(长度)}
        for (auto it = itl; it != itr; ++it)
        {
            vp.push_back({it->v, it->r - it->l + 1});
        }
        sort(vp.begin(), vp.end());
        for (const auto &p : vp)
        {
            k -= p.second;
            if (k <= 0)
                return p.first;
        }
        return -1LL;
    }
    // 通用区间查询范例：求区间每个元素的 x 次方和 % mod
    long long pow_sum(int l, int r, int ex, long long mod)
    {
        auto itr = split(r + 1);
        auto itl = split(l);

        auto qpow = [&](long long a, long long b)
        {
            long long res = 1;
            a %= mod;
            while (b > 0)
            {
                if (b & 1)
                    res = (__int128)res * a % mod;
                a = (__int128)a * a % mod;
                b >>= 1;
            }
            return res;
        };

        long long ans = 0;
        for (auto it = itl; it != itr; ++it)
        {
            long long len = it->r - it->l + 1;
            ans = (ans + len * qpow(it->v, ex)) % mod;
        }
        return ans;
    }
}odt;
int n,m,seed,vmax,x,y;
int rnd(){
    int res=seed;
    seed=(seed*7+13)%1000000007;
    return res;
}
void solved(){
    cin>>n>>m>>seed>>vmax;
    for(int i=1;i<=n;i++){
        odt.s.insert({i,i,(rnd()%vmax)+1});
    }
    for(int i=1;i<=m;i++){
        int op=rnd()%4+1;
        int l=rnd()%n+1;
        int r=rnd()%n+1;
        if(l>r)swap(l,r);
        if(op==3){
            x=rnd()%(r-l+1)+1;
        }else{
            x=rnd()%vmax+1;
        }
        if(op==4){
            y=rnd()%vmax+1;
        }
        if(op==1){
            odt.add(l,r,x);
        }else if(op==2){
            odt.assign(l,r,x);
        }else if(op==3){
            cout<<odt.kth(l,r,x)<<endl;
        }else if(op==4){
            cout<<odt.pow_sum(l,r,x,y)<<endl;
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
