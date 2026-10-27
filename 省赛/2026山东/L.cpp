#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXP = 1000000;
vector<int> primes;
vector<bool> isComp;

// 埃氏筛：预处理 1e6 内质数
void sieve()
{
    isComp.assign(MAXP + 1, false);
    for (int i = 2; i <= MAXP; i++)
    {
        if (!isComp[i])
        {
            primes.push_back(i);
            if ((ll)i * i <= MAXP)
                for (ll j = (ll)i * i; j <= MAXP; j += i)
                    isComp[j] = true;
        }
    }
}

// 分解 d 的不同质因子（d <= 1e12）
vector<ll> distinctPrimeFactors(ll d)
{
    vector<ll> res;
    for (int p : primes)
    {
        if ((ll)p * p > d)
            break;
        if (d % p == 0)
        {
            res.push_back(p);
            while (d % p == 0)
                d /= p;
        }
    }
    if (d > 1)
        res.push_back(d); // 剩下的一定是质数
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    sieve();

    int T;
    cin >> T;
    while (T--)
    {
        ll a, b;
        int q;
        cin >> a >> b >> q;
        ll d0 = llabs(a - b);
        vector<ll> pf;
        if (d0 > 1)
            pf = distinctPrimeFactors(d0);

        while (q--)
        {
            ll k;
            cin >> k;

            ll A = a, B = b, d = d0, time = k;

            if (d == 0)
            { // a = b = 1，永远 1/1
                cout << "1 1\n";
                continue;
            }

            while (time > 0 && d > 1)
            {
                // 下一次约分的最小时刻 t*
                ll best = LLONG_MAX;
                for (ll p : pf)
                {
                    if (d % p)
                        continue; // 该质因子已不在当前 d 中
                    ll r = A % p;
                    ll t = (r == 0) ? p : (p - r);
                    if (t < best)
                        best = t;
                }

                if (best > time)
                { // 剩余时间内不会约分
                    A += time;
                    B += time;
                    time = 0;
                    break;
                }

                time -= best;
                A += best;
                B += best;

                ll g = std::gcd(A, d); 
                A /= g;
                B /= g;
                d /= g;
            }

            if (time > 0)
            {
                A += time;
                B += time;
            } // d 已为 1，之后不再约分
            cout << A << " " << B << "\n";
        }
    }
    return 0;
}