#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin>>n;
    
    vector<vector<long long>> d(n + 1, vector<long long>(n + 1));
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            cin >> d[i][j];
        }
    }
    int k;
    cin >> k;
    while (k--)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        if (w < d[u][v])
        {
            d[u][v] = d[v][u] = w;
        }
        long long total_sum = 0;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                d[i][j] = min(d[i][j], d[i][u] + d[u][v] + d[v][j]);
                d[i][j] = min(d[i][j], d[i][v] + d[v][u] + d[u][j]);
                if (i < j)
                {
                    total_sum += d[i][j]; // 只累加无向图的单向点对
                }
            }
        }
        cout << total_sum << (k == 0 ? "" : " ");
    }
    cout << "\n";
    return 0;
}