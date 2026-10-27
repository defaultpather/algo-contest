#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long
void solved(){
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    vector<int> val(n - 3); 
    map<int, int> cnt;
    for (int x = 1; x + 4 <= n; x++)
    {
        val[x] =a[x] + a[x + 2] - a[x + 4];
        cnt[val[x]]++;
    }
    int ans = 0;
    for (auto [k, v] : cnt)
    {
        ans += v * (v - 1) / 2;
    }
    for (int x = 1; x + 2 <= n - 4; x++)
    { 
        if (val[x] == val[x + 2])
            ans--;
    }
    for (int x = 1; x + 4 <= n - 4; x++)
    { 
        if (val[x] == val[x + 4])
            ans--;
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
