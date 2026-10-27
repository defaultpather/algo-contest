#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;
int fo(int x, int k)
{
    int a = x * x + k * k;
    int mo = a % 8;
    return mo ^ k;
}
int g(int x, int k)
{
    int temp = x;
    queue<int> s;
    for (int i = 8; i >= 0; i--)
    {
        if (temp >= pow(2, i))
        {
            s.push(1);
            temp = temp - pow(2, i);
        }
        else
        {
            s.push(0);
        }
    }
    int a = 0;
    for (int i = 2; i >= 0; i--)
    {
        int m = s.front();
        a += m * pow(2, i);
        s.pop();
    }
    int b = 0;
    for (int i = 2; i >= 0; i--)
    {
        int m = s.front();
        b += m * pow(2, i);
        s.pop();
    }
    int c = 0;
    for (int i = 2; i >= 0; i--)
    {
        int m = s.front();
        c = c + m * pow(2, i);
        s.pop();
    }
    int d = b;
    int e = c ^ fo(b, k);
    int h = a ^ fo(c, k);
    int ans = h + e * pow(2, 3) + d * pow(2, 6);
    return ans;
}
int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> k(m + 1);
    vector<int> a(n + 1);
    for (int i = 1; i <= m; i++)
        cin >> k[i];
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
    {
        vector<int> f(m + 1);
        int mo = m;
        f[mo] = a[i];
        while (mo >= 1)
        {
            for (int j = 0; j < pow(2, 9); j++)
            {
                if (g(j, k[mo]) == f[mo])
                {
                    f[mo - 1] = j;
                    break;
                }
            }
            mo--;
        }
        cout << f[0] << " ";
    }
    return 0;
}