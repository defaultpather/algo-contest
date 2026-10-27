#include<bits/stdc++.h>
using namespace std;

#define int long long

void solved(){
    int xm,ym,xc,yc;
    cin>>xm>>ym>>xc>>yc;
    vector<vector<int>>g(10,vector<int>(11,0));
    
    for(int i=1;i<=10;i++){
        g[xc][i]=1;
    }
    for(int i=1;i<=9;i++){
        g[i][yc]=1;
    }
    const int INF=1e9;
    auto check = [&](int x1, int y1,int x2,int y2)
    {
        vector<pair<int, int>> pos(8,{1e9,1e9});
        if(x2!=x1+1||y2!=y1){
            pos[0].first = x1 + 2, pos[0].second = y1 + 1;
            pos[1].first = x1 + 2, pos[1].second = y1 - 1;
        }
        if(x2!=x1-1||y2!=y1){
            pos[2].first = x1 - 2, pos[2].second = y1 + 1;
            pos[3].first = x1 - 2, pos[3].second = y1 - 1;
        }
        if(y2!=y1+1||x1!=x2){
            pos[4].first = x1 + 1, pos[4].second = y1 + 2;
            pos[5].first = x1 - 1, pos[5].second = y1 + 2;
        }
        if(y2!=y1-1||x1!=x2){
            pos[6].first = x1 + 1, pos[6].second = y1 - 2;
            pos[7].first = x1 - 1, pos[7].second = y1 - 2;
        }
        for (int i = 0; i < 8; i++){
            auto [x, y] = pos[i];
            if (x >= 1 && x <= 9 && y >= 1 && y <= 10&&x!=INF&&y!=INF){
                if(x==x2&&y==y2){
                    return false;
                }
                if(g[x][y]==0){
                    // cout<<111<<"\n";
                    return false;
                }
            }
        }
        return true;
    };
    if(check(xm,ym,xc,yc)){
        cout<<"YES\n";
    }else{
        cout<<"NO\n";
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T=1;
    cin>>T;
    while(T--){
        solved();
    }
}