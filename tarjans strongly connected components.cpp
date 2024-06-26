vector<int> tin(MAXN, 0), low(MAXN, 0), stak;
vector<bool> onStack(MAXN, false);
int timer = 0, sccCount = 0;
void dfs(int at){
    stak.push_back(at);
    onStack[at] = true;
    tin[at] = low[at] = ++timer;

    for(int to : adj[at]) {
        if(!tin[to]) dfs(to);
        if(onStack[to]) low[at] = min(low[at], low[to]);
    }

    if(tin[at] == low[at]) {
        for(int node = stak.back(); ; node = stak.back()){
            stak.pop_back();
            onStack[node] = false;
            low[node] = tin[at];
            if(at == node) break;
        }
        ++sccCount;
    }
}

for(int i = 0; i < n; i++)
    if(!tin[to])
        dfs(i);
