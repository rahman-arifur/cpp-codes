struct DSU{
private:
    vector<int> par, sz;
    int n, compo;
public:
    DSU(int c) : n(c), compo(c) {
        par.resize(n + 1);
        iota(par.begin(), par.end(), 0);
        sz = vector<int> (n + 1, 1);
    }
    int getCompo() { return compo; }
    int getSize(int v) { return sz[find(v)]; }
    int find(int v) {  while(v!=par[v])v=par[v]=par[par[v]]; return v;  }
    bool same(int u, int v) {  return find(u) == find(v);  } 
    bool unite(int u, int v) {
        u = find(u), v = find(v);
        if(u==v) return false; compo--;
        if(sz[u] > sz[v]) swap(u, v);
        par[u] = v;
        return sz[v] += sz[u];
    }
};
