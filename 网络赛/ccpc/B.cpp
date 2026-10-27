#include<bits/stdc++.h>
using namespace std;

#define int long long

void solved(){
    array<int,6>a{};
    for(int i=0;i<6;i++){
        cin>>a[i];
    }
    int k;
    cin>>k;
    vector<int>cand={1};
    for(int i=0;i<6;i++)cand.push_back(a[i]+1);
    array<int,6>best{};
    int tot=1;
    for(int i=0;i<6;i++){
        tot*=7;
    }
    int bestSum=LLONG_MAX;
    for(int o=0;o<tot;o++){
        int t=o;
        array<int,6>b{};
        int sum=0;
        int win=0;
        for(int j=0;j<6;j++){
            b[j]=cand[t%7];
            t/=7;
            sum+=b[j];
            for(int i=0;i<6;i++){
                if(a[i]<b[j])
                    win++;
            }
        }
        if(win>=19&&sum<=bestSum){
            best=b;
            bestSum=min(bestSum,sum);
        }
    }
    if(bestSum>k){
        cout<<"NO\n";
    }else{
        cout<<"YES\n";
        best[0]+=k-bestSum;
        for(int i=0;i<6;i++){
            cout<<best[i]<<" \n"[i==5];
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