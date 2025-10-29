vector<int> adj[N];
bool point[N];
int timer, tin[N], low[N];
void dfs(int v, int p = -1) {
  tin[v] = low[v] = ++timer;
  int child = 0;
  for (int to : adj[v]) {
    if (to == p) continue;
    if (vis[to]) {
      low[v] = min(low[v], tin[to]);
    } else {
      dfs(to, v);
      low[v] = min(low[v], low[to]);
      if (low[to] >= tin[v] && p != -1)
        IS_CUTPOINT(v); // point[v] = true;
      ++child;
    }
  }
  if (p == -1 && child > 1)
    IS_CUTPOINT(v); // point[v] = true;
}
for (int i = 0; i < n; ++i) {
  if (!vis[i]) dfs(i);
}
