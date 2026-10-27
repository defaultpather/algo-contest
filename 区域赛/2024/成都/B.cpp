#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N=305;
const int mod=1e9+7;
int f[N][N][3],g[N][N][3];
int ans[N][N][N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n,q;
    cin>>n>>q;
    string  s;
    cin>>s;
    s=' '+s;
    f[0][0][0]=f[0][0][1]=f[0][0][2]=1;
    int tot=0;
    for(int i=1;i<=n;i++){
        memcpy(g,f,sizeof f);
        memset(f,0,sizeof f);
        if(s[i]!='?'){
            char op=s[i]-'a';
            for(int x=0;x<=tot;x++){
                for(int y=0;y+x<=tot;y++){
                    for(int o=0;o<3;o++){
                        if(o!=op){
                            (f[x][y][op]+=g[x][y][o])%=mod;
                        }
                    }
                }
            }
        }else{
            for(int x=0;x<=tot;x++){
                for(int y=0;y+x<=tot;y++){
                    for(int o=0;o<3;o++){
                        if(o!=0)
                            (f[x+1][y][0]+=g[x][y][o])%=mod;
                        if(o!=1)
                            (f[x][y+1][1]+=g[x][y][o])%=mod;
                        if(o!=2)
                            (f[x][y][2]+=g[x][y][o])%=mod;
                    }
                }
            }
            tot++;
        }
    }
    for(int x=0;x<=tot;x++){
        for(int y=0;y+x<=tot;y++){
            for(int o=0;o<3;o++){
                ans[x][y][tot-x-y]+=f[x][y][o];
            }
            ans[x][y][tot-x-y]=ans[x][y][tot-x-y]%mod*((mod+1)>>1)%mod;                
        }
    }
    for(int x=0;x<=300;x++)
        for(int y=0;y<=300;y++)
            for(int z=1;z<=300;z++)
                (ans[x][y][z]+=ans[x][y][z-1])%=mod;
    for (int x = 0; x <= 300; x++)
        for (int y = 1; y <= 300; y++)
            for (int z = 0; z <= 300; z++)
                (ans[x][y][z] += ans[x][y-1][z]) %= mod;
    for (int x = 1; x <= 300; x++)
        for (int y = 0; y <= 300; y++)
            for (int z = 0; z <= 300; z++)
                (ans[x][y][z] += ans[x-1][y][z]) %= mod;
    while(q--){
        int x,y,z;
        cin>>x>>y>>z;
        cout<<ans[x][y][z]<<"\n";
    }
}