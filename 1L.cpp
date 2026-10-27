#include <bits/stdc++.h>
using i64 = long long;
using namespace std;


struct group{
  int val;
  double st;
  bool operator<(const group& other)const {
        if(other.val==val){
            return st>other.st;
        }else{
            return val<other.val;
        }
  }  
};
void solved(){
    priority_queue<group>pq;
}
signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int T = 1;
    while (T--)
    {
        solved();
    }
}