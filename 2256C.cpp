#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

#define endl '\n'
#define int long long
void solved()
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    int c1 = 0, c2 = 0;

    for (int i = 0; i < n * 2; i++)
    {
        int i1 = (i + 1) % (n * 2); 

        if (s[i] == '1')
        { 
            if (s[i1] == '1')
            { 
                if (i % 2 == 0)
                    c1++; 
                else
                    c2++; 
            }
            else
            { 
                if (i % 2 == 0)
                    c2++;
                else
                    c1++;
            }
        }
    }
    cout << c2 << " " << c1 << endl;
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
