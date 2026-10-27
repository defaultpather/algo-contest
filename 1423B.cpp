#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct Edge
{
    int u, v, w;
};

struct Dinic
{
    struct GraphEdge
    {
        int to, cap, flow, rev;
    };
    int n, s, t;
    vector<vector<GraphEdge>> adj;
    vector<int> level, ptr;

    Dinic(int n, int s, int t) : n(n), s(s), t(t), adj(n), level(n), ptr(n) {}

    void add_edge(int from, int to, int cap)
    {
        adj[from].push_back({to, cap, 0, (int)adj[to].size()});
        adj[to].push_back({from, 0, 0, (int)adj[from].size() - 1});
    }

    bool bfs()
    {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            for (auto &edge : adj[v])
            {
                if (edge.cap - edge.flow > 0 && level[edge.to] == -1)
                {
                    level[edge.to] = level[v] + 1;
                    q.push(edge.to);
                }
            }
        }
        return level[t] != -1;
    }

    int dfs(int v, int pushed)
    {
        if (pushed == 0 || v == t)
            return pushed;
        for (int &cid = ptr[v]; cid < adj[v].size(); ++cid)
        {
            auto &edge = adj[v][cid];
            int tr = edge.to;
            if (level[v] + 1 != level[tr] || edge.cap - edge.flow == 0)
                continue;
            int tr_pushed = dfs(tr, min(pushed, edge.cap - edge.flow));
            if (tr_pushed == 0)
                continue;
            edge.flow += tr_pushed;
            adj[tr][edge.rev].flow -= tr_pushed;
            return tr_pushed;
        }
        return 0;
    }

    int max_flow()
    {
        int flow = 0;
        while (bfs())
        {
            fill(ptr.begin(), ptr.end(), 0);
            while (int pushed = dfs(s, INF))
            {
                flow += pushed;
            }
        }
        return flow;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    int max_w = 0;
    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        max_w = max(max_w, edges[i].w);
    }
    auto check = [&](int x)
    {
        int S = 0, T = 2 * n + 1;
        Dinic dinic(T + 1, S, T);

        for (int i = 1; i <= n; i++)
            dinic.add_edge(S, i, 1);
        for (int i = 1; i <= n; i++)
            dinic.add_edge(n + i, T, 1);
        for (const auto &e : edges)
        {
            if (e.w <= x)
            {
                dinic.add_edge(e.u, n + e.v, 1);
            }
        }
        return dinic.max_flow() == n;
    };

    int lo = 1, hi = max_w, ans = -1;
    while (lo <= hi)
    {
        int mid = lo + (hi - lo) / 2;
        if (check(mid))
        {
            ans = mid;
            hi = mid - 1; // 尝试寻找更小的可行解
        }
        else
        {
            lo = mid + 1;
        }
    }

    cout << ans << "\n";
    return 0;
}