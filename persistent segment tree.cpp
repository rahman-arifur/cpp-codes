#include <bits/stdc++.h>
using namespace std;
// 0 based version and array
struct PersistentSegTree {
    struct Node {
        long long val;
        int lc, rc;
    };

    vector<Node> tree;
    vector<int> roots; // Stores the root node index for each version
    int n;

    // Initialize with the maximum size of the array
    PersistentSegTree(int size, int qry) : n(size) {
        int m = 1 + 4 * n + (__lg(n) + 2) * qry;
        tree.reserve(m);
        roots.reserve(m);
        tree.push_back({0, 0, 0}); 
        roots.push_back(0); 
    }

    int cloneNode(int v) {
        tree.push_back(tree[v]);
        return tree.size() - 1;
    }

    // Build the initial version (Version 0) from an array
    int build(int l, int r, const vector<int>& a) {
        int v = tree.size();
        tree.push_back({0, 0, 0});
        if (l == r) {
            tree[v].val = a[l];
            return v;
        }
        int mid = l + (r - l) / 2;
        tree[v].lc = build(l, mid, a);
        tree[v].rc = build(mid + 1, r, a);
        tree[v].val = tree[tree[v].lc].val + tree[tree[v].rc].val;
        return v;
    }

    void build_initial(const vector<int>& a) {
        roots[0] = build(0, n - 1, a);
    }

    // Point update: returns the root of the newly created version
    int update(int prev_v, int l, int r, int idx, int val) {
        int v = cloneNode(prev_v);
        
        if (l == r) {
            tree[v].val = val; // Set the new value (or use += for incrementing)
            return v;
        }
        
        int mid = l + (r - l) / 2;
        if (idx <= mid) {
            tree[v].lc = update(tree[prev_v].lc, l, mid, idx, val);
        } else {
            tree[v].rc = update(tree[prev_v].rc, mid + 1, r, idx, val);
        }
        
        // Push up
        tree[v].val = tree[tree[v].lc].val + tree[tree[v].rc].val;
        return v;
    }

    // Wrapper to update and save the new version root
    void add_version(int prev_version, int idx, int val) {
        int new_root = update(roots[prev_version], 0, n - 1, idx, val);
        roots.push_back(new_root);
    }

    // Range query on a specific version
    long long query(int v, int l, int r, int ql, int qr) {
        // Out of bounds or null node
        if (ql > r || qr < l || v == 0) return 0; 
        
        // Fully within bounds
        if (ql <= l && r <= qr) return tree[v].val;
        
        // Partial overlap
        int mid = l + (r - l) / 2;
        return query(tree[v].lc, l, mid, ql, qr) + 
               query(tree[v].rc, mid + 1, r, ql, qr);
    }

    // Wrapper for clean querying
    long long query_version(int version, int ql, int qr) {
        return query(roots[version], 0, n - 1, ql, qr);
    }
};
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin>>n>>q;
    vector<int> a(n);
    for(auto& i: a) cin>>i;
    PersistentSegTree pst(n, q);
    pst.build_initial(a);
    while(q--) {
        int type, ver;
        cin>>type>>ver;
        --ver;
        if(1 == type) {
            int a, x;
            cin>>a>>x;
            a--;
            pst.roots[ver] = pst.update(pst.roots[ver], 0, n - 1, a, x);
        } else if(2 == type) {
            int l, r;
            cin>>l>>r;
            --l,--r;
            cout << pst.query_version(ver, l, r) << '\n';
        } else {
            pst.roots.push_back(pst.roots[ver]);
        }
    }
    // https://cses.fi/problemset/task/1737
    return 0;
}
