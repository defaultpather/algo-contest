#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

#define int  long long

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x;
    cin>>x;
    if(x==0){
        cout<<1<<"\n";
    }else if(x==1){
        cout<<"10\n";
    }
    else if (x == 2)
    {
        cout << "22\n";
    }
    else if (x == 3)
    {
        cout << "222\n";
    }
    else
    {
        cout << -1 << '\n';
    }
    // for(int bit=1;bit<=10;bit++){
    //     vector<array<int,3>>p(bit,array<int,3>{});
    //     for(int i=0;i<bit;i++){
    //         for(int j=0;j<3;j++){
    //             p[i][j]=j;
    //         }
    //     }
    // }

    return 0;
}
