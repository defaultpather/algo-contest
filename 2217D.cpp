#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> arr(n + 2);
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    vector<int> pivots(k + 2);
    for (int i = 1; i <= k; i++)
    {
        cin >> pivots[i];
    }
    arr[0] = arr[n + 1] = arr[pivots[1]];
    pivots[k + 1] = n + 1;

    int S = 0, X = 0;
    for (int i = 0; i <= k; i++)
    {
        int count = 0;
        for (int j = pivots[i]; j < pivots[i + 1]; j++)
        {
            if (arr[j] != arr[j + 1])
            {
                // cout<<"j: "<<j<<" ";
                count++;
            }
        }
        S += count;
        // cout<<"count: "<<count<<endl;
        X = max(X, count);
    }

    cout << max(S / 2, X) << "\n";
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}