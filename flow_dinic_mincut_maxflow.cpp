#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 1LL << 60;
// tophhh
struct Edge {
    int from, to;
    ll cap, flow;
    Edge(int from, int to, ll cap, ll flow) 
        : from(from), to(to), cap(cap), flow(flow) {}
};

struct Dinic {
    int n;
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<int> level, ptr;

    Dinic(int n) : n(n) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int from, int to, ll cap, bool is_directed = true) {
        adj[from].emplace_back(edges.size());
        edges.emplace_back(from, to, cap, 0LL);
        adj[to].emplace_back(edges.size());
        edges.emplace_back(to, from, is_directed ? 0LL : cap, 0LL);
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.emplace(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1) continue;
                if (level[edges[id].to] != -1) continue;
                level[edges[id].to] = level[v] + 1;
                q.emplace(edges[id].to);
            }
        }
        return level[t] != -1;
    }

    ll dfs(int v, int t, ll pushed) {
        if (pushed == 0 || v == t) return pushed;
        for (int& cid = ptr[v]; cid < adj[v].size(); ++cid) {
            int id = adj[v][cid];
            int to = edges[id].to;
            if (level[v] + 1 != level[to] || edges[id].cap - edges[id].flow < 1) continue;
            ll push = dfs(to, t, min(pushed, edges[id].cap - edges[id].flow));
            if (push == 0) continue;
            edges[id].flow += push;
            edges[id ^ 1].flow -= push;
            return push;
        }
        return 0;
    }

    ll max_flow(int s, int t) {
        ll flow = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (ll pushed = dfs(s, t, INF)) {
                flow += pushed;
            }
        }
        return flow;
    }

    vector<pair<int, int>> get_min_cut(int s) {
        vector<bool> vis(n, false);
        queue<int> q;
        q.emplace(s);
        vis[s] = true;

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow > 0 && !vis[edges[id].to]) {
                    vis[edges[id].to] = true;
                    q.emplace(edges[id].to);
                }
            }
        }

        vector<pair<int, int>> cutset;
        for (int i = 0; i < edges.size(); i += 2) {
            if (vis[edges[i].from] != vis[edges[i].to]) {
                cutset.emplace_back(edges[i].from, edges[i].to);
            }
        }
        return cutset;
    }
};
// https://cses.fi/problemset/task/1695
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    Dinic flow(n);
    for(int i = 0, u, v; i < m; i++) {
        cin >> u>> v;
        --u; v--;
        flow.add_edge(u, v, 1, false);
    }
    cout << flow.max_flow(0, n - 1) << '\n';
    auto res = flow.get_min_cut(0);
    for(auto& [u, v]: res) {
        cout << u + 1 << ' ' << v + 1 << '\n';
    }
return 0;
  // if we keep holding onto yesterday, what are we going to be tomorrow?
}
