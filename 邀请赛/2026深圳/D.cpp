#include<bits/stdc++.h>
using namespace std;

#define int long long

void solved(){
    int n;
    cin>>n;
    vector<pair<int,int>>ev;
    for(int i=0;i<n;i++){
        char c;
        cin>>c;
        if(c=='W'){
            ev.push_back({0,0});
        }else{
            int x;
            cin>>x;
            ev.push_back({1,x});
        }
    }
    multiset<pair<int,int>>s1,s2;
    int sum_a=0,sum_b=0;
    int W=0,i=0;
    auto ins=[&](pair<int,int>x)->void{
        if(W==0){
            s2.insert(x);
            return;
        }
        if(s1.size()<W){
            s1.insert(x);
            sum_a+=x.first;
            sum_b+=x.second;
            return;
        }
        if(*s1.begin()<x){
            auto q=*s1.begin();
            s1.erase(s1.begin());
            sum_a-=q.first;
            sum_b-=q.second;
            s2.insert(q);

            s1.insert(x);
            sum_a+=x.first;
            sum_b+=x.second;
        }else{
            s2.insert(x);
        }
    };
    auto update=[&](){
        while(s1.size()<W&&!s2.empty()){
            auto q=prev(s2.end());
            s1.insert(*q);
            sum_a+=q->first;
            sum_b+=q->second;
            s2.erase(q);
        }
    };
    auto del=[&](auto x){
        auto p=s1.find(x);
        if(p!=s1.end()){
            sum_a-=p->first;
            sum_b-=p->second;
            s1.erase(p);
            if(!s2.empty()){
                auto q=prev(s2.end());
                s1.insert(*q);
                sum_a+=q->first;
                sum_b+=q->second;
                s2.erase(q);
            }
        }else{
            s2.erase(s2.find(x));
        }
    };  
    int ans=0ll;
    while(i<n){
        if(ev[i].first==1){
            ins(make_pair(ev[i].second,0ll));
            i++;
            continue;
        }
        W++;
        update();
        int r=i+1;
        while(r<n&&ev[r].first==1)
            r++;
        int len=r-i;
        vector<pair<int,int>>tmp;
        for(int k=1;k<len;k++){
            int y=ev[i+k].second;
            int prof=y*(len-k);
            auto p=make_pair(prof/len,prof%len);
            tmp.push_back(p);
            ins(p);
        }
        update();
        ans+=(sum_a*len+sum_b);
        for(auto p:tmp)
            del(p);
        for(int k=1;k<len;k++){
            ins(make_pair(ev[i+k].second,0ll));
        }
        i=r;
    }
    cout<<ans<<'\n';
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