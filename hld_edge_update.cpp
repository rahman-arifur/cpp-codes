struct LazySegTree {
    int n;
    vector<ll> tree, lazy;

    LazySegTree(int n) : n(n), tree(4 * n, 0), lazy(4 * n, 0) {}

    void build(int node, int l, int r, const vector<ll>& flat_a) {
        if (l == r) {
            tree[node] = flat_a[l];
            return;
        }
        int mid = l + (r - l) / 2;
        build(node * 2, l, mid, flat_a);
        build(node * 2 + 1, mid + 1, r, flat_a);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    void push(int node, int l, int r) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node] * (r - l + 1); 
            if (l != r) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void update(int node, int l, int r, int ql, int qr, ll val) {
        push(node, l, r);
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            lazy[node] += val;
            push(node, l, r);
            return;
        }
        int mid = l + (r - l) / 2;
        update(node * 2, l, mid, ql, qr, val);
        update(node * 2 + 1, mid + 1, r, ql, qr, val);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    ll query(int node, int l, int r, int ql, int qr) {
        push(node, l, r);
        if (ql > r || qr < l) return 0; 
        if (ql <= l && r <= qr) return tree[node];
        int mid = l + (r - l) / 2;
        return query(node * 2, l, mid, ql, qr) + 
               query(node * 2 + 1, mid + 1, r, ql, qr);
    }
};

struct EdgeHLD {
    int n, timer;
    vector<vector<pair<int, ll>>> adj; // {neighbor, edge_weight}
    vector<int> parent, depth, head, pos, sz, heavy;
    vector<ll> node_edge_val; // Stores the weight of the edge above this node
    LazySegTree seg;

    EdgeHLD(int n) : n(n), timer(0), adj(n), parent(n), depth(n), head(n), 
                     pos(n), sz(n), heavy(n, -1), node_edge_val(n, 0), seg(n) {}

    void add_edge(int u, int v, ll w = 0) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void dfs_sz(int v = 0, int p = -1, int d = 0) {
        sz[v] = 1;
        parent[v] = p;
        depth[v] = d;
        int max_sub = 0;
        for (auto& edge : adj[v]) {
            int to = edge.first;
            ll w = edge.second;
            if (to != p) {
                node_edge_val[to] = w; // Push the edge weight into the deeper child
                dfs_sz(to, v, d + 1);
                sz[v] += sz[to];
                if (sz[to] > max_sub) {
                    max_sub = sz[to];
                    heavy[v] = to;
                }
            }
        }
    }

    void dfs_hld(int v = 0, int p = -1, int h = 0) {
        head[v] = h;
        pos[v] = timer++;
        if (heavy[v] != -1) {
            dfs_hld(heavy[v], v, h);
        }
        for (auto& edge : adj[v]) {
            int to = edge.first;
            if (to != p && to != heavy[v]) {
                dfs_hld(to, v, to);
            }
        }
    }

    void build(int root = 0) {
        dfs_sz(root);
        dfs_hld(root);
        
        // Load the edge values into the Segment Tree
        vector<ll> flat_vals(n);
        for (int i = 0; i < n; i++) {
            flat_vals[pos[i]] = node_edge_val[i];
        }
        seg.build(1, 0, n - 1, flat_vals);
    }

    // --- EDGE PATH UPDATE ---
    void update_path(int u, int v, ll val) {
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) swap(u, v);
            seg.update(1, 0, n - 1, pos[head[u]], pos[u], val);
            u = parent[head[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        
        // CRUCIAL DIFFERENCE: pos[u] + 1
        // Since u is the LCA, node 'u' holds the edge ABOVE the LCA. We skip it!
        if (u != v) {
            seg.update(1, 0, n - 1, pos[u] + 1, pos[v], val);
        }
    }

    // --- EDGE PATH QUERY ---
    ll query_path(int u, int v) {
        ll res = 0;
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) swap(u, v);
            res += seg.query(1, 0, n - 1, pos[head[u]], pos[u]);
            u = parent[head[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        
        // CRUCIAL DIFFERENCE: pos[u] + 1 skips the LCA's upward edge
        if (u != v) {
            res += seg.query(1, 0, n - 1, pos[u] + 1, pos[v]);
        }
        return res;
    }
    
    // Helper to update a single specific edge
    void update_single_edge(int u, int v, ll val) {
        // The edge is stored in whichever node is deeper
        if (depth[u] < depth[v]) swap(u, v);
        seg.update(1, 0, n - 1, pos[u], pos[u], val);
    }
};
