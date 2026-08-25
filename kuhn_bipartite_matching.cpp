#include "bits/stdc++.h"
using namespace std;

struct Kuhn {
    int n, m;
    vector<vector<int>> adj;
    vector<int> match_v; 
    vector<int> vis;
    int timer;

    Kuhn(int n, int m) : n(n), m(m) {
        adj.resize(n);
        match_v.assign(m, -1);
        vis.assign(m, 0);
        timer = -100000;
    }

    void add_edge(int u, int v) {
        adj[u].emplace_back(v);
    }

    bool dfs(int u) {
        for (int v : adj[u]) {
            if (vis[v] == timer) continue;
            vis[v] = timer;
            if (match_v[v] == -1 || dfs(match_v[v])) {
                match_v[v] = u;
                return true;
            }
        }
        return false;
    }

    int max_matching() {
        int matches = 0;
        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        for (int u = 0; u < n; u++) {
            shuffle(adj[u].begin(), adj[u].end(), rng);
        }
        
        vector<bool> matched_u(n, false);
        for (int u = 0; u < n; u++) {
            for (int& v : adj[u]) {
                if (match_v[v] == -1) {
                    match_v[v] = u;
                    matched_u[u] = true;
                    matches++;
                    break;
                }
            }
        }
        
        for (int u = 0; u < n; u++) {
            if (!matched_u[u]) {
                timer++;
                if (dfs(u)) {
                    matches++;
                }
            }
        }
        return matches;
    }
    
    vector<pair<int, int>> get_matches() {
        vector<pair<int, int>> pairs;
        for (int v = 0; v < m; v++) {
            if (match_v[v] != -1) {
                pairs.emplace_back(match_v[v], v); 
            }
        }
        return pairs;
    }
};
vector<pair<int, int>> dirs = { {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2} };
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector bad(n, vector<char>(m, 0));
    for(int i = 0, x, y; i < k; i++) {
        cin >> x >> y;
        --x, y--;
        bad[x][y] = 1;
    }
    auto ok = [&](int i, int j) -> bool {
        return min(i, j) >= 0 and i < n and j < m and !bad[i][j];
    };
    Kuhn gg(n * m, n * m);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) if(!bad[i][j] and 0 == (i + j) % 2) {
            int ij = i * m + j;
            for(auto& [di, dj]: dirs) {
                int x = i + di, y = j + dj;
                if(!ok(x, y)) continue;
                int xy = x * m + y;
                gg.add_edge(ij, xy);
            }
        }
    }
    cout << n * m - k - gg.max_matching() << '\n';
}
// https://lightoj.com/problem/knights-in-chessboard-ii
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t, tc = 1; cin >> t;
    while(t-- > 0) {
        cout << "Case " << tc++ << ": ";
        solve();
    }
return 0;
}
