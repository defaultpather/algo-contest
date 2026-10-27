#include<bits/stdc++.h>
using namespace std;

struct LineRange{
    int r,mn,mx;
};
signed main(){
    int n,m;
    cin>>n>>m;
    vector<vector<LineRange>>pos(n*m+10);
    for(int r=1;r<=n;r++){
        for(int c=1;c<=m;c++){
            int x;
            cin>>x;
            if(pos[x].empty()||pos[x].back().r!=r){
                pos[x].push_back({r,c,c});
            }else{
                pos[x].back().mx=c;
            }
        }
    }
    vector<vector<int>>diff(n+2,vector<int>(m+2,0));
    for(int x=1;x<=n*m;x++){
        int sz=pos[x].size();
        if(sz<2)continue;
        vector<int>suf_mx(sz),pre_mn(sz);
        suf_mx[sz-1]=pos[x][sz-1].mx;
        for(int i=sz-2;i>=0;i--){
            suf_mx[i]=max(suf_mx[i+1],pos[x][i].mx);
        }
        pre_mn[0]=pos[x][0].mn;
        for(int i=1;i<sz;i++){
            pre_mn[i]=min(pre_mn[i-1],pos[x][i].mn);
        }
        for(int k=0;k+1<sz;k++){
            int c1=pre_mn[k];
            int c2=suf_mx[k+1];
            if(c1<c2){
                int r1=pos[x][k].r;
                int r2=pos[x][k+1].r;
                diff[r1][c1]++;
                diff[r1][c2+1]--;
                diff[r2+1][c1]--;
                diff[r2+1][c2+1]++;
            }
        }
    }
    for(int r=1;r<=n;r++){
        for(int c=1;c<=m;c++){
            diff[r][c]+=diff[r-1][c]+diff[r][c-1]-diff[r-1][c-1];
        }
    }
    for(int r=1;r<=n;r++){
        string ans="";
        for(int c=1;c<=m;c++){
            if(diff[r][c]>0){
                ans+="1";
            }else{
                ans+="0";
            }
        }
        cout<<ans<<endl;
    }
}