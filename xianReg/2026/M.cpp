
#include <bits/stdc++.h>
using namespace std;

#define int long long

void solved()
{
    int n;
    cin >> n;
    vector<string> s(4);
    for (int i = 0; i < 4; i++)
    {
        cin >> s[i];
    }
    array<int, 4> H{};
    array<int, 4> life;
    array<bool, 4> ok;

    life.fill(2000);
    ok.fill(true);
    for (int i = 0; i < n; i++)
    {
        array<int, 4> de{};
        array<bool, 4> up{};
        for (int j = 0; j < 4; j++){
            char c = s[j][i];
            // char c = s[j][min((int)s[j].size(), i)];
            if (c == 'H'){
                H[j]++;
                if (H[j] == 100){
                    H[j] = 0;
                    up[j] = true;
                }
            }else{
                H[j] = 0;
                if (c == 'J')
                    de[j] = 50;
                else if (c == 'A')
                    de[j] = 100;
                else if (c == 'M')
                    de[j] = 200;
            }
        }
        for (int j = 0; j < 4; j++){
            if (!ok[j])
                continue;
            int h = 0;
            for (int o = 0; o < 4; o++){
                if (o != j && up[o]){
                    h += 30;
                }
            }
            life[j] += h;
            life[j] -= de[j];
            life[j] = min(2000LL, life[j]);
            if (life[j] <= 0){
                life[j] = 0;
                ok[j] = 0;
            }
        }
    }
    for (int i = 0; i < 4; i++){
        cout << life[i] << " ";
    }
    cout<<"\n";
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--){
        solved();
    }
    return 0;
}
