#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
#define endl '\n'
int main() {
    int n;
    cin >> n;
    set<i64> st;
    vector<i64> a(n);
    for(auto &i:a) cin >> i;
    for(int i = 0; i < a.size() - 1; i++) {
        i64 x = a[i], y = a[i + 1];
        st.insert(0);
        st.insert(x);
        st.insert(y);
        st.insert(x | y);
        st.insert(x & y);
        st.insert(x ^ y);
        st.insert((~x) & y);
        st.insert((~y) & x);
    }
    cout << st.size();
}
