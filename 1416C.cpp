/**
 *    author:  tourist
 *    created: 27.09.2020 18:09:48
 *    problem: CF1416C XOR Inverse
 *    做法:   按「两数最高的不同二进制位」把逆序对分桶, 每位独立贪心, O(30 * n log n)
 **/

#undef _GLIBCXX_DEBUG
// 若编译时带了 -D_GLIBCXX_DEBUG (STL 调试模式: 迭代器/越界检查), sort/vector 会慢好几倍;
// 这句强制取消. 没定义过时 #undef 也无副作用, 属于防御性提速.

#include <bits/stdc++.h>
// GCC 万能头: vector / tuple / algorithm / iostream 一次全包

using namespace std;
// 省去到处写 std::

int main()
{
    ios::sync_with_stdio(false);
    // 关闭 C(stdio) 与 C++(iostream) 的同步, cin/cout 提速到接近 scanf/printf.
    // 副作用: 此后不要混用 scanf/printf 与 cin/cout.
    cin.tie(0);
    // 解除 cin 与 cout 的绑定 (0 即 nullptr), 避免每次读入前 flush cout.

    int n; // 数列长度, n <= 3e5
    cin >> n;
    vector<int> a(n); // 原数列, a[i] <= 1e9 < 2^30, int 足够
    for (int i = 0; i < n; i++)
    {
        cin >> a[i]; // 读入后全程不再修改 a
    }

    // 三元组: (高于 bit 的所有位 a[i]>>(bit+1) , 原下标 i , 第 bit 位)
    //   分量1 相同 <=> 两个数在 bit 以上完全相同 => 这一对应该在 bit 这一层结算
    //   分量2 放原下标, 使"前缀相同的元素"排序后仍按原下标升序排列
    vector<tuple<int, int, int>> v(n); // 在 30 次循环外分配一次, 循环内复用
    long long ans = 0;                 // 最小逆序对数, 最坏 n(n-1)/2 ≈ 4.5e10, 必须 long long
    int x = 0;                         // 待输出的 x, 逐位累加, 最大 2^30-1

    for (int bit = 0; bit < 30; bit++)
    {
        // 只枚举 0..29: a[i] < 2^30, 第 30 位以上所有数恒为 0,
        // 翻转它们不改变任何大小关系, 永远不会被选进 x.
        // 从低到高枚举没问题: 各位决策互相独立, x 只是按位累加.

        for (int i = 0; i < n; i++)
        {
            v[i] = make_tuple(a[i] >> (bit + 1),  // ① 前缀: bit 以上的所有位
                              i,                  // ② 原下标: 作为第二关键字, 保证组内按原序
                              (a[i] >> bit) & 1); // ③ 第 bit 位 (&1 不能省, 否则带出高位)
        }
        sort(v.begin(), v.end());
        // 字典序排序: 先按前缀分组, 组内再按原下标升序.
        // 第二关键字是 i 是整份代码的关键: 组内扫描顺序 = 原数组顺序,
        // 才能用"前面的数 / 后面的数"来数逆序对.
        // 若写成 (前缀, 该位, 下标), 组内会被拆成 0 块和 1 块, 计数就错了.

        long long inv0 = 0; // 本层 x 的第 bit 位取 0 时, 产生的逆序对数
        long long inv1 = 0; // 本层 x 的第 bit 位取 1 时, 产生的逆序对数
        int beg = 0;        // 当前组的左端点
        while (beg < n)
        {
            int end = beg;
            // 前缀(第 0 分量)相同就继续往右扩; end+1 < n 防越界.
            // 注意只比 get<0>: 若比整个 tuple, 因下标互不相同会永远不等, 退化成每组一个元素.
            while (end + 1 < n && get<0>(v[end + 1]) == get<0>(v[end]))
            {
                ++end;
            }
            // 退出时 [beg, end] 是一个前缀相同的组, 且组内按原下标升序.

            int k0 = 0; // 组内扫描至今, 第 bit 位为 0 的元素个数 (<= n, int 够)
            int k1 = 0; // 组内扫描至今, 第 bit 位为 1 的元素个数
            for (int i = beg; i <= end; i++)
            {
                int bit = get<2>(v[i]); // 取该元素第 bit 位; 注意这个 bit 遮蔽了外层循环变量, 逻辑正确但易误读
                if (bit == 0)
                {
                    // 当前是 0: 和前面每个 1 组成 (前1, 后0) 对.
                    // x 的该位取 0 时, 前 1 后 0 就是逆序 => inv0 加上 k1 个.
                    inv0 += k1;
                    k0 += 1; // 当前 0 加入"已见过的 0"
                }
                else
                {
                    // 当前是 1: 和前面每个 0 组成 (前0, 后1) 对.
                    // x 的该位取 1 时两人同时翻转, 变成"前 1 后 0" => inv1 加上 k0 个.
                    inv1 += k0;
                    k1 += 1; // 当前 1 加入"已见过的 1"
                }
            }
            beg = end + 1; // 处理下一组
        }
        // 本层代价只由 x 的第 bit 位决定, 取较小者:
        // 相等时用 <= 选 0 (tie-break), 保证在逆序对最少的前提下 x 最小.
        if (inv0 <= inv1)
        {
            ans += inv0; // 该位取 0
        }
        else
        {
            ans += inv1;     // 该位取 1
            x += (1 << bit); // 把这一位记入 x, 等价于 x |= 1 << bit
        }
    }

    cout << ans << " " << x << '\n'; // 先逆序对数, 后 x
    return 0;
}