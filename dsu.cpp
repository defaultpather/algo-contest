struct DSU{
    vector<int> fa, siz;
    DSU() {}

    DSU(int n){
        init(n);
    }

    void init(int n){
        fa.resize(n);
        iota(fa.begin(), fa.end(), 0);
        siz.assign(n, 1);
    }

    int find(int u){
        return u == fa[u] ? u : fa[u] = find(fa[u]);
    }

    bool same(int u, int v){
        return find(u) == find(v);
    }

    bool merge(int u, int v){
        u = find(u);
        v = find(v);
        if (u == v){
            return false;
        }
        siz[u] += siz[v];
        fa[v] = u; // x为主
        return true;
    }

    int size(int u){
        return siz[find(u)];
    }
};
