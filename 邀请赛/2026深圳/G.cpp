//矩阵转置
#include<bits/stdc++.h>
using namespace std;

#define int long long
pair<int,int>tmp[55][55],nxt[55][55];
void solved(){
    int n,m,rs,cs;
    cin>>n>>m>>rs>>cs;
    bool swp=false;
    if(!(m&1)){
        swap(n,m);
        swp=true;
    }
    bool odd=false;
    if(!(n&1)){
        for(int i=1;i<=n;i++){
            if(i&1){
                for(int j=2;j<m;j++){
                    nxt[i][j]={i,j+1};
                }
                nxt[i][m]={i+1,m};
            }else{
                for(int j=m;j>2;j--){
                    nxt[i][j]={i,j-1};
                }
                if(i==n)
                    nxt[i][2]={n,1};
                else 
                    nxt[i][2]={i+1,2};
            }
        }
        for(int i=n;i>1;i--){
            nxt[i][1]={i-1,1};
        }
        nxt[1][1]={1,2};
    }else{
        for(int i=1;i<n-1;i++){
            if(i&1){
                for(int j=2;j<m;j++){
                    nxt[i][j]={i,j+1};
                }
                nxt[i][m]={i+1,m};
            }else{
                for(int j=m;j>2;j--){
                    nxt[i][j]={i,j-1};
                }
                nxt[i][2]={i+1,2};
            }
        }
        for(int j=m;j>2;j-=2){
            nxt[n-1][j]={n,j};
            nxt[n][j]={n,j-1};
            nxt[n][j-1]={n-1,j-1};
            nxt[n-1][j-1]={n-1,j-2};
        }
        for(int i=n-1;i>1;i--){
            nxt[i][1]={i-1,1};
        }
        nxt[n][1]={n-1,1};
        nxt[1][1]={1,2};
        odd=true;
    }
    if(swp){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                tmp[j][i]=nxt[i][j];
                swap(tmp[j][i].first,tmp[j][i].second);
            }
        }
        swap(n,m);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                nxt[i][j]=tmp[i][j];
            }
        }
    }
    auto walk=[&]()->char{
        char res;
        auto [x,y]=nxt[rs][cs];
        if(x>rs){
            res='D';
        }else if(x<rs){
            res='U';
        }else if(y>cs){
            res='R';
        }else if(y<cs){
            res='L';
        }
        rs=x,cs=y;
        return res;
    };
    for(int i=1;i<n*m;i++){
        int r,c;
        cin>>r>>c;
        string s;
        if(odd){
            if(make_pair(r,c)==make_pair(n,1)&&nxt[n][2]!=make_pair(r,c)){
                nxt[n][2]={n,1};
            }else if(make_pair(r,c)!=make_pair(n,1)&&nxt[n][2]==make_pair(n,1)){
                nxt[n][2]={n-1,2};
            }
        }
        while(rs!=r||cs!=c){
            s+=walk();
        }
        cout<<s<<endl;
    }
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