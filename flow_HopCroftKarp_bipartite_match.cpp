#include "bits/stdc++.h"
using namespace std;

struct HopcroftKarp {
    int n, m;
    vector<vector<int>> adj;
    vector<int> match_u, match_v, dist;
    const int INF = 1e9;

    // n = size of Left set (U), m = size of Right set (V)
    HopcroftKarp(int n, int m) : n(n), m(m) {
        adj.resize(n);
        match_u.assign(n, -1);
        match_v.assign(m, -1);
        dist.resize(n + 1);
    }

    // Add a directed edge from u (in Left set) to v (in Right set)
    // Both u and v should be 0-indexed: u in [0, n-1], v in [0, m-1]
    void add_edge(int u, int v) {
        adj[u].emplace_back(v);
    }

    bool bfs() {
        queue<int> q;
        // dist[n] acts as a dummy node for "unmatched"
        for (int u = 0; u < n; ++u) {
            if (match_u[u] == -1) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = INF;
            }
        }
        dist[n] = INF;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            // If we haven't found a shorter augmenting path yet
            if (dist[u] < dist[n]) {
                for (int v : adj[u]) {
                    // Next node in U is the one currently matched to v
                    int next_u = match_v[v];
                    if (next_u == -1) next_u = n; // redirect to dummy node if unmatched

                    if (dist[next_u] == INF) {
                        dist[next_u] = dist[u] + 1;
                        q.push(next_u);
                    }
                }
            }
        }
        return dist[n] != INF;
    }

    bool dfs(int u) {
        if (u != n) {
            for (int v : adj[u]) {
                int next_u = match_v[v];
                if (next_u == -1) next_u = n;

                if (dist[next_u] == dist[u] + 1) {
                    if (dfs(next_u)) {
                        match_v[v] = u;
                        match_u[u] = v;
                        return true;
                    }
                }
            }
            dist[u] = INF; // Dead-end elimination
            return false;
        }
        return true;
    }

    int max_matching() {
        int matching = 0;
        while (bfs()) {
            for (int u = 0; u < n; ++u) {
                if (match_u[u] == -1) {
                    if (dfs(u)) {
                        matching++;
                    }
                }
            }
        }
        return matching;
    }
};
// https://cses.fi/problemset/task/1696
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, q;
    cin >> n >> m >> q;
    HopcroftKarp flow(n, m);
    for(int i = 0, u, v; i < q; i++) {
        cin >> u >> v;
        --u, v--;
        flow.add_edge(u, v);
    }
    cout << flow.max_matching() << '\n';
    for(int i = 0; i < n; i++) {
        if(flow.match_u[i] != -1) {
            cout << i + 1 << ' ' << flow.match_u[i] + 1 << '\n';
        }
    }
return 0;
}
