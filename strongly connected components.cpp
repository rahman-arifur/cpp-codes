const int mxn = 100003;
vector<int> adj[mxn], stak;
int tin[mxn], low[mxn], n, color[mxn]// component no 1 based;
bool onstack[mxn];
int timer = 0, sccCount = 0;
void dfs(int at) {
	stak.push_back(at);
	onstack[at] = true;
	tin[at] = low[at] = ++timer;

	for (int to : adj[at]) {
		if (!tin[to]) {
			dfs(to);
			low[at] = min(low[at], low[to]);
		} else if (onstack[to])
			low[at] = min(low[at], tin[to]);
	}

	if (tin[at] == low[at]) {
		++sccCount;
		while (1) {
			int node = stak.back();
			stak.pop_back();
			onstack[node] = false;
			color[node] = sccCount;
			if (node == at) break;
		}
	}
}
for (int i = 1; i <= n; i++)
		if (!tin[i]) dfs(i);
