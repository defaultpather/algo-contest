#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

#define endl '\n'
#define int long long
void solved(){
    int n;
    cin >> n;
    vector<int> d(n);
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        d[i] = a - (i + 1); 
    }
    sort(d.begin(), d.end());
    d.erase(unique(d.begin(), d.end()), d.end());

    int ans = 1, cur = 1;
    for (int i = 1; i < (int)d.size(); i++)
    {
        if (d[i] == d[i - 1] + 1)
            cur++;
        else
            cur = 1;
        ans = max(ans, cur);
    }
    cout << ans << "\n";
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t=1;
    cin>>t;
    while(t--){
        solved();
    }
    return 0;
}
