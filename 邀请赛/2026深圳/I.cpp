#include<bits/stdc++.h>
using namespace std;

#define int long long
void solved(){
    string x;
    cin>>x;
    int a=stoi(x);
    
    if(a>=1&&a<=8){
        cout << "Yes\n";
        for(int i=0;i<12;i++){
            if(i<a){
                cout<<i<<" ";
            }else{
                cout<<0<<" ";
            }
        }
        cout<<"\n";
    }else if(a==11){
        cout<<"Yes\n";
        cout<<"0 1 2 3 4 5 "<<"6 7 8 0 0 0\n";
    }else if(a==22){
        cout<<"Yes\n";
        cout<<"0 1 2 3 4 5 "<<"6 7 8 1 0 0\n";
    }else if(a==33){
        cout<<"Yes\n";
        cout<<"0 1 2 3 4 5 "<<"6 7 8 1 2 0\n";
    }else{
        cout<<"No\n";
    }
    // if(a==9||a==10||a>=12&&a<22){
    //     cout<<"No\n";
    //     return;
    // }
    // if(a>=1&&a<=6){
    //     cout<<"Yes\n";
    //     for(int i=0;i<6;i++){
    //         if(i<a){
    //             cout<<i<<" ";
    //         }else{
    //             cout<<0<<" ";
    //         }
    //     }
    //     for(int i=0;i<6;i++){
    //         cout<<0<<" \n"[i==5];
    //     }
    // }else if(a>6&&a<=11){
    //     cout<<"Yes\n";
    //     for(int i=0;i<6;i++){
    //         cout<<i<<" ";
    //     }
    //     if(a==6){
    //         cout << "0 0 0 0 0 0\n";
    //     }else if(a==7){
    //         cout << "6 0 0 0 0 0\n";
    //     }else if(a==8){
    //         cout << "6 7 0 0 0 0\n";
    //     }else if(a==11){
    //         cout << "6 7 8 0 0 0\n";
    //     }
    // }
    // else if(a>33){
    //     cout<<"No\n";
    // }else if(a>22){
    //     cout<<"Yes\n";
    //     array<int, 12> ans = {
    //         0, 1, 2, 3, 4, 5,
    //         0, 6, 7, 8, 1, 2};
    //     for(int i=0;i<12;i++){
    //         cout<<ans[i]<<" \n"[i==11];
    //     }
    // }

}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t=1;
    cin>>t;
    while(t--){
        solved();
    }
}