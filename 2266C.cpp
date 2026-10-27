#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

#define endl '\n'
#define int long long
void solved(){
    int n;
    string s;
    cin >> n >> s;
    if(is_sorted(s.begin(),s.end())){
        cout<<0<<endl;
        return;
    }
    if(s[0]=='1'){
        cout<<count(s.begin(),s.end(),'0')<<endl;
        return;
    }
    vector<int> pre1(n + 1, 0);
    for (int i = 0; i < n; i++)
        pre1[i + 1] = pre1[i] + (s[i] == '1');
    int tot0 = n - pre1[n];
    int ans = n;
    for (int k = 0; k <= n; k++)
    {
        int cost = pre1[k] + (tot0 - (k - pre1[k]));
        ans = min(ans, cost);
    }
    cout << ans << endl;
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
