#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long
const double linf=1e18;
void solved(){
    int n,m;
    cin>>n>>m;
    int B=n+m;
    vector<pair<int,int>>pos(B+1);
    pos[0]={0,0};
    for(int i=1;i<=B;i++){
        cin>>pos[i].first>>pos[i].second;
    }
    vector<vector<double>>dis(B+1,vector<double>(B+1,linf));
    dis[0][0]=0;
    for(int i=0;i<=B;i++){
        for(int j=0;j<=B;j++){
            double x=pos[i].first-pos[j].first;
            double y=pos[i].second-pos[j].second;
            dis[i][j]=dis[j][i]=sqrt(x*x+y*y);
            // dis[i][j]=dis[j][i]=x+y;
        }
    }
    //dp[s][u]表示在s状态下到达u点所需的最少时间
    vector<vector<double>>dp(1<<B,vector<double>(B+1,linf));
    dp[0][0]=0;
    for(int s=0;s<(1ll<<B);s++){
        int boost=0;
        for(int i=0;i<m;i++){
            if((s>>(i+n)&1)){
                boost++;
            }
        }
        double speed=(1ll<<boost);
        for(int u=0;u<=B;u++){
            if(dp[s][u]==linf)continue;
            for(int v=1;v<=B;v++){
                if(!(s>>(v-1)&1)){
                    double time=dis[u][v]/speed;
                    int next_s=s|(1ll<<(v-1));
                    if(dp[s][u]+time<dp[next_s][v]){
                        dp[next_s][v]=dp[s][u]+time;
                    }
                }
            }
        }
    }
    double ans=linf;
    int all_mask=(1ll<<n)-1;
    for(int s=0;s<(1ll<<B);s++){
        if((s&all_mask)==all_mask){
            int boost =0;
            for(int i=0;i<m;i++){
                if(s>>(i+n)&1){
                    boost++;
                }
            }
            double speed=1ll<<boost;
            for(int u=0;u<=B;u++){
                if(dp[s][u]!=linf){
                    double time=dis[u][0]/speed;
                    ans=min(ans,dp[s][u]+time);
                }
            }
        }
    }
    cout<<fixed<<setprecision(10)<<ans<<endl;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T=1;
    // cin>>T;
    while(T--){
       solved();
    }
    return 0;
}
