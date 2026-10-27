#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int u, v, c, id;
};

void solved()
{
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    int max_c = 0;
    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].c;
        edges[i].u--;
        edges[i].v--;
        edges[i].id = i + 1;
        max_c = max(max_c, edges[i].c);
    }
    vector<int> pos(n);
    auto check = [&](int mid) -> bool
    {
        vector<int> in(n, 0);
        vector<vector<int>> adj(n);

        for (auto &e : edges)
        {
            if (e.c > mid)
            {
                adj[e.u].push_back(e.v);
                in[e.v]++;
            }
        }
        queue<int> q;
        for (int i = 0; i < n; i++)
        {
            if (in[i] == 0)
            {
                q.push(i);
            }
        }
        int cnt = 0;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            pos[u] = ++cnt; 
            for (int v : adj[u])
            {
                if (--in[v] == 0)
                {
                    q.push(v);
                }
            }
        }
        return cnt == n;
    };
    int lo = 0, hi = max_c, ans_c = max_c;
    while (lo <= hi)
    {
        int mid = lo + (hi - lo) / 2;
        if (check(mid))
        {
            ans_c = mid; 
            hi = mid - 1;
        }
        else
        {
            lo = mid + 1;
        }
    }
    check(ans_c);
    vector<int> rev_edges;
    for (const auto &e : edges)
    {
        if (e.c <= ans_c && pos[e.u] > pos[e.v])
        {
            rev_edges.push_back(e.id);
        }
    }
    cout << ans_c << " " << rev_edges.size() << "\n";
    for (int i = 0; i < rev_edges.size(); i++)
    {
        cout << rev_edges[i]<<" ";
    }
    cout << "\n";
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solved();
    return 0;
}