#include <iostream>
#include <algorithm>

using namespace std;

typedef __int128_t int128; // 使用 128 位整数防止中间乘法溢出

long long x, a, b;

// 计算在总回合数为 T，且前 k 回合叠毒的情况下，T 回合内造成的总伤害
int128 get_damage(long long T, long long k)
{
    if (k > T)
        return 0;

    // 普攻伤害
    int128 attack_damage = (int128)(T - k) * b;

    // 中毒伤害计算：
    // 前 k 回合：第 i 回合施加 a 层毒，结算时毒层数为 i*a。
    // 在这 k 回合结算中，总共造成的毒伤害为 a + 2a + ... + ka = a * k * (k + 1) / 2
    int128 poison_sum_k = (int128)a * k * (k + 1) / 2;

    // 在第 k 回合结束、完成结算后，剩余的中毒层数为 P = k*a - k
    int128 P = (int128)k * a - k;
    if (P < 0)
        P = 0;

    // 剩余的 T - k 回合中，毒层数每回合减少 1（加上结算时的 -1，相当于每回合毒递减 1）
    // 剩余 T - k 回合能造成的毒伤害为：P + (P-1) + ... + (P - (T-k) + 1)
    long long rem_turns = T - k;
    int128 remaining_poison_damage = 0;
    if (P > 0)
    {
        if (P <= rem_turns)
        {
            // 毒会在 rem_turns 回合内衰减到 0
            remaining_poison_damage = P * (P + 1) / 2;
        }
        else
        {
            // 毒在 T 回合结束时还没衰减完
            remaining_poison_damage = (P + (P - rem_turns + 1)) * rem_turns / 2;
        }
    }

    return attack_damage + poison_sum_k + remaining_poison_damage;
}

// 检查 T 回合内是否能够击杀敌人
bool check(long long T)
{
    // 尝试不同的 k（叠毒回合数）
    // k 的最大范围不需要太大，超过 2,000,000 时中毒伤害已经远超 10^18
    long long max_k = min(T, 2000000LL);

    for (long long k = 0; k <= max_k; ++k)
    {
        if (get_damage(T, k) >= x)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    // 快速输入输出
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> x >> a >> b))
        return 0;

    // 二分答案查找最少回合数 T
    long long left = 1, right = x; // 最坏情况：全用普攻，需要 x/b 上取整回合，最大不超过 x
    long long ans = right;

    while (left <= right)
    {
        long long mid = left + (right - left) / 2;
        if (check(mid))
        {
            ans = mid;
            right = mid - 1; // 尝试寻找更小的回合数
        }
        else
        {
            left = mid + 1; // 回合数不够，增加回合数
        }
    }

    cout << ans << "\n";

    return 0;
}