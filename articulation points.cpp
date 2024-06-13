
vector<int> tin, low;
int timer;

vector<bool> vis, point;
void dfs(int v, int p = -1) {
  vis[v] = true;
  tin[v] = low[v] = timer++;
  int children = 0;
  for (int to : adj[v]) {
    if (to == p)
      continue;
    if (vis[to]) {
      low[v] = min(low[v], tin[to]);
    } else {
      dfs(to, v);
      low[v] = min(low[v], low[to]);
      if (low[to] >= tin[v] && p != -1)
        IS_CUTPOINT(v); // point[v] = true;
      ++children;
    }
  }
  if (p == -1 && children > 1)
    IS_CUTPOINT(v); // point[v] = true;
}


for (int i = 0; i < n; ++i) {
  if (!vis[i])
    dfs(i);
}
