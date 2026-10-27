#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin>>n;
    string s1,s2,s3;
    int c;
    for(int i=0;i<n;i++){
        cin>>s1>>s2>>s3;
        cin>>c;
        if(c){
            cout << "gdut_" << s1 << " " << s2 << " " << s3 << endl;
        }
    }



    return 0;
}
