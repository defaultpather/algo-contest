#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// ============================================================
// S1: 当前"前 W 大"的二元组；S2: 其余二元组
// 每个二元组 (a,b) 表示真实收益 P = a*len + b，0 <= b < len
// 这样按 (a,b) 字典序比较 = 按 P 比较，且与 len 无关
// ============================================================
multiset<pair<ll, ll>> S1, S2;

ll W = 0;                // 当前工人数（每遇到一次 W 加 1）
ll sum_a = 0, sum_b = 0; // S1 里所有二元组的 a 之和、b 之和

// ------------------------------------------------------------
// 插入一个二元组 p
// 维护不变量：|S1| = min(W, |S1|+|S2|)，且 S1 是最大的那些
// ------------------------------------------------------------
void ins(pair<ll, ll> p)
{
    if (W == 0)
    { // 还没有工人，任何工厂都进不了前 W 大
        S2.insert(p);
        return;
    }

    if ((ll)S1.size() < W)
    { // S1 还没装满 W 个，直接放进去
        S1.insert(p);
        sum_a += p.first;  // 维护 S1 的 a 之和
        sum_b += p.second; // 维护 S1 的 b 之和
        return;
    }

    // 走到这里说明 S1 已经满了（|S1| == W）
    if (p > *S1.begin())
    {                         // p 比 S1 里最小的那个还大：替换
        auto q = *S1.begin(); // q = S1 当前最小值
        S1.erase(S1.begin()); // 从 S1 删掉 q
        sum_a -= q.first;     // 同步更新和
        sum_b -= q.second;
        S2.insert(q); // q 退到 S2

        S1.insert(p); // p 进 S1
        sum_a += p.first;
        sum_b += p.second;
    }
    else
    {
        S2.insert(p); // p 不够大，进 S2
    }
}

// ------------------------------------------------------------
// 删除一个二元组 p
// 如果删的是 S1 里的，需要从 S2 补一个最大的回来
// ------------------------------------------------------------
void rem(pair<ll, ll> p)
{
    auto it1 = S1.find(p); // 先在 S1 里找
    if (it1 != S1.end())
    {                  // 在 S1 里
        S1.erase(it1); // 删掉
        sum_a -= p.first;
        sum_b -= p.second;

        if (!S2.empty())
        {                              // S1 少了一个，从 S2 拿最大的补上
            auto it2 = prev(S2.end()); // S2 的最大值（multiset 有序）
            auto q = *it2;
            S2.erase(it2);
            S1.insert(q);
            sum_a += q.first;
            sum_b += q.second;
        }
    }
    else
    { // 不在 S1，就在 S2
        auto it2 = S2.find(p);
        S2.erase(it2);
    }
}

// ------------------------------------------------------------
// W 增加后调用：把 S2 中最大的若干元素补进 S1，直到 |S1| == W
// （W 增加只会让 S1 需要多装，补的最多 1 个）
// ------------------------------------------------------------
void reb()
{
    while ((ll)S1.size() < W && !S2.empty())
    {
        auto it = prev(S2.end()); // S2 最大
        auto q = *it;
        S2.erase(it);
        S1.insert(q);
        sum_a += q.first;
        sum_b += q.second;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n; // 事件数

    // ev[i].first: 0 表示 W（工人），1 表示 F（工厂）
    // ev[i].second: 工厂的产能（W 时无用）
    vector<pair<int, ll>> ev(n);

    for (int i = 0; i < n; i++)
    {
        string t;
        cin >> t; // 读事件类型
        if (t == "W" || t == "1")
        {
            ev[i] = {0, 0}; // 工人
        }
        else
        {
            ll x;
            cin >> x; // 工厂产能
            ev[i] = {1, x};
        }
    }

    ll ans = 0; // 总收益
    int i = 0;

    while (i < n)
    {
        // 第一个 W 之前的工厂：没有工人，不产生收益，
        // 但它们是"已有工厂"，先以 (x,0) 形式放进集合
        if (ev[i].first == 1)
        {
            ins({ev[i].second, 0});
            i++;
            continue;
        }

        // ================= 一个以 W 开头的段 =================
        W++;   // 新工人到来
        reb(); // 让 S1 重新装满前 W 大

        // 找这一段的结束位置：下一个 W（或数组末尾）
        int j = i + 1;
        while (j < n && ev[j].first == 1)
            j++;

        int len = j - i; // 本段天数（含 W 当天）

        // 1) 把段内新工厂的收益变成二元组插进集合
        vector<pair<ll, ll>> fp; // 记录插入的二元组，后面要删
        for (int t = 1; t < len; t++)
        {
            ll y = ev[i + t].second;     // 第 t 天建的新工厂
            ll prof = y * (ll)(len - t); // 它能工作 len-t 天
            // 真实收益 prof 拆成 (a,b)，满足 prof = a*len + b
            pair<ll, ll> p = {prof / len, prof % len};
            fp.push_back(p);
            ins(p); // 插进 S1/S2
        }

        // 2) 调整：保证 |S1| = min(W, 总元素数)
        reb();

        // 3) 本段答案 = S1 中所有真实收益之和
        //    每个 (a,b) 的收益是 a*len+b，所以总和 = len*sum_a + sum_b
        ans += (ll)len * sum_a + sum_b;

        // 4) 删掉段内新工厂的二元组
        //    （它们的 a,b 依赖本段 len，不能留到下一段）
        for (auto &p : fp)
            rem(p);

        // 5) 新工厂转为"已有工厂"：以 (y,0) 重新插入
        //    (y,0) 与 len 无关，下一段自动表示 y*新len
        for (int t = 1; t < len; t++)
        {
            ll y = ev[i + t].second;
            ins({y, 0});
        }

        i = j; // 跳到下一段
    }

    cout << ans << '\n';
    return 0;
}