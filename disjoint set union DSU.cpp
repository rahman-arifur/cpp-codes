struct DSU{
    vector<int> parent, sizes;
    int n;
    DSU(int c) : n(c) {
        parent.resize(n + 1);
        iota(begin(parent), end(parent), 0);
        sizes = vector<int> (n + 1, 1);
    }
    int find(int v) {
        while(v != parent[v])
            v = parent[v] = parent[parent[v]];
        return v;
    }
    bool same(int u, int v) {
        return find(u) == find(v);
    }
    void unite(int u, int v) {
        u = find(u), v = find(v);
        if(u == v) return;
        if(sizes[u] > sizes[v]) swap(u, v);
        parent[u] = v;
        sizes[v] += sizes[u];
    }
};
