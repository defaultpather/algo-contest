#include <bits/stdc++.h>
using namespace std;
using i64 = long long;//constexpr 0LL
using pii = pair<int, int>; 
#define endl '\n'
#define xx first
#define yy second
#define debug(x) (cout << "@ " << #x << " = " << x << endl)
constexpr i64 linf = 1e18;
constexpr int inf = 1e9;
constexpr int MOD = 1e9+7;
constexpr int N = 5e5-10;
void solved(){
    int a,b,c;
    cin>>a>>b>>c;
    string x1,x2,y1,y2;
    x1="3"+string(N,'0');
    x2="3"+string(N,'0');
    y1=string(N,'3')+"3";
    y2=string(N,'3')+"4";
    cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    int T=1;
    // cin>>T;
    while(T--){
       solved();
    }
    return 0;
}
