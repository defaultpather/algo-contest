#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 r,g,b;
    cin>>r>>g>>b;
    i64 tot=r+g+b;
    i64 mx=max({r,g,b});
    cout<<min(tot/3,tot-mx)<<'\n';
    return 0;
}
