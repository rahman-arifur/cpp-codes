vector<int> adj[N];
int timer, tin[N], low[N];
void dfs(int v, int p = -1) {
    tin[v] = low[v] = ++timer;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (tin[to]) 
            low[v] = min(low[v], tin[to]);
        else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v])
                IS_BRIDGE(v, to);
        }
    }
}
