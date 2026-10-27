#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
#define endl '\n'
struct P {
    i64 id, score; //id和得分
};

bool cmp(const P &x, const P &y) {
    if(x.score == y.score) {
        return x.id < y.id;
    }
    return x.score > y.score;
}


void solve() {
    i64 n, m, q;
    cin >> n >> m >> q;
    vector<P> player(m + 1);

    for(int i = 1; i <= m; i++) {
        auto &[id, score] = player[i];
        id = i, score = 0;
    }
    vector<bool> ignore(m + 1, 0); //当前已完成或者放弃当前关卡

    i64 win_score = 0; //在当前关卡能获得的分数
    i64 active_attack = -1; //当前活跃的关卡
    while (q--) {
        i64 type;
        cin >> type;
        if(type == 1) {
            i64 x;
            cin >> x;
            active_attack = x;
            win_score = m;
            ignore.assign(m + 1, 0);
            continue;
        } 

        if(type == 2) {
            i64 id, x;
            cin >> id >> x;
            if(x != active_attack) continue;
            if(ignore[id] == 1) continue;
            auto &[id_1, score] = player[id];
            ignore[id] = 1;
            score += win_score;
            win_score--;
            continue;
        }

        if(type == 3) {
            i64 id, x;
            cin >> id >> x;
            if(x != active_attack) continue;
            if(ignore[id] == 1) continue;
            auto &[id_1, score] = player[id];
            ignore[id] = 1;
            continue;
        }
    }
    sort(player.begin() + 1, player.end(), cmp);
    for(int i = 1; i <= m; i++) {
        auto &[id, score] = player[i];
        cout << id << ' ' << score << endl;
    }
}


int main() {
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    
}
