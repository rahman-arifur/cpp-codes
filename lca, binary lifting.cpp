int N, LG, timer;
vector<vector<int>> adj, up;
vector<int> tin, tout, ans;
void dfs(int v, int p)
{
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= LG; ++i)
        up[v][i] = up[up[v][i-1]][i-1];
    for (int u : adj[v]) if (u != p)dfs(u, v);
    tout[v] = ++timer;
}
bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}
int lca(int u, int v)
{
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;
    for (int i = LG; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}
void preprocess(int root) {
    tin.resize(N);
    tout.resize(N);
    ans.resize(N,0);
    timer = 0;
    LG = ceil(log2(N));
    up.assign(N, vector<int>(LG + 1));
    dfs(root, root);
}
