#include<bits/stdc++.h>
using namespace std;

#define int long long

void solved(){
    // int n;
    // cin>>n;
    // vector<int>p1(n+1),p2(n+1);
    // iota(p1.begin(),p1.end(),0);
    // iota(p2.begin(),p2.end(),0);
    // set<int>s;
    // do{
    //     // for(int i=1;i<=n;i++){
    //     //     cout<<p2[i]<<" \n"[i==n];
    //     // }
    //     int gd=0;
    //     for(int i=1;i<=n;i++){
    //         gd=__gcd(p1[i]*p2[i],gd);
    //     }
    //     if(n%2==0&&gd==2){
    //         for(int i=1;i<=n;i++){
    //             cout<<p2[i]<<" \n"[i==n];
    //         }
    //         cout<<endl;
    //         break;
    //     }
    //     // cout<<gd<<endl;
    //     s.insert(gd);
    // }while(next_permutation(p2.begin()+1,p2.end()));
    // // for(auto c:s){
    // //     cout<<c<<" ";
    // // }
    // // cout<<endl;
    int n;
    cin>>n;
    vector<int>p(n+1);
    iota(p.begin(),p.end(),0);
    if(n&1){
        for(int i=1;i<=n;i++){
            cout<<i<< " \n"[i==n];
        }
    }else{
        for(int i=1;i<=n;i+=2){
            /*
                2 1 4 3 6 5 8 7 10 9 12 11
                1 2 3 4 5 6 7 8 9 10 11 12
            */
           cout<<i+1<<" "<<i<<" \n"[i==n];
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T=1;
    // cin>>T;
    while(T--){
        solved();
    }
}