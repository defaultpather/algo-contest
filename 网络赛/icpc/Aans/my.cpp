#include<bits/stdc++.h>
using namespace std;

// #define int long long

#define debug(x) (cout<<#x<<" = "<<x<<"\n")

void solved(){
    int n;
    cin>>n;
    vector<char>c(n);
    vector<int>a(n);
    for(int i=0;i<n;i++){
        cin>>c[i]>>a[i];
    }
    vector<pair<int,int>>order(n);
    for(int i=0;i<n;i++){
        order[i]={a[i],i};
    }
    sort(order.begin(),order.end());
    // for(int i=0;i<n;i++){
    //     cout<<order[i].first<<" "<<order[i].second<<"\n";
    // }
    vector<int>keep(n);
    for(int l=0;l<n;){
        int push_ok=-1,lastT=-1;
        int r=l;
        while(r<n&&order[r].first==order[l].first)
            r++;
        // cout<<r<<endl;
        for(int k=l;k<r;k++){
            auto [val,idx]=order[k];
            if(c[idx]=='+'){
                // debug(k);
                // debug(c[idx]);
                // debug(a[idx]);
                // debug(idx);
                if(push_ok!=-1){
                    // debug(c[idx]);
                    // debug(idx);
                    // debug(val);
                    keep[push_ok]=(lastT==-1?push_ok:lastT);
                    // debug(keep[idx]);
                }
                push_ok=idx;
                // debug(push_ok);
                lastT=-1;
            }else if(c[idx]=='T'){
                // debug(k);
                if(push_ok!=-1)
                    lastT=idx;
                    // debug(lastT);
            }else if(c[idx]=='F'){
                if(push_ok!=-1){
                    // debug(c[idx]);
                    // debug(val);
                    // debug(idx);
                    keep[push_ok]=(lastT!=-1?lastT:push_ok);
                    // debug(keep[idx]);
                }
                // debug(keep[idx]);
                push_ok=-1;
                lastT=-1;
            }
            // debug(push_ok);
            // debug(keep[idx]);
            // debug(lastT);
        }
        if(push_ok!=-1){
            keep[push_ok]=(lastT!=-1?lastT:push_ok);
        }
        l=r;
    }
    // for(int i=0;i<n;i++){
    //     cout<<keep[i]<<" ";
    // }
    // cout<<endl;
    stack<pair<int,int>>stk;
    set<int>s;
    string out;
    auto POP=[&](){
        s.erase(stk.top().first);
        stk.pop();
        out.push_back('-');
    };
    for(int i=0;i<n;i++){
        if(c[i]=='+'){
            int x=a[i];
            if(s.contains(x)){
                while(!stk.empty()&&stk.top().first!=x)POP();
                POP();
            }
            stk.push({x,keep[i]});
            s.insert(x);    
            out.push_back('+');
        }else if(c[i]=='T'){
            out.push_back('?');
        }else if(c[i]=='F'){
            int x=a[i];
            if(s.contains(x)){
                while(!stk.empty()&&stk.top().first!=x)POP();
                POP();
            }
            out.push_back('?');
        }
        // cout<<"i: "<<i<<" && "<<out<<"\n";
        // if(stk.empty())continue;
        // if(!stk.empty()){
        //     debug(stk.top().second);
        //     debug(i);
        // }
        while(!stk.empty()&&stk.top().second<=i)POP();
        // cout << "i: " << i << " && " << out << "\n";
    }
    cout<<out<<"\n";
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