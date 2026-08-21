#include <iostream>
#include <vector>

using namespace std;

struct Node {
    long long val;
    int lc, rc;
    Node(long long v = 0) : val(v), lc(0), rc(0) {}
    Node(const Node& oth) {
        val = oth.val; lc = oth.lc; rc = oth.rc;
    }    
    friend Node merge(const Node& a, const Node& b) {
        return Node(a.val + b.val); 
    }
};

template <typename T>
struct PersistentSegTree {
    int n;
    vector<T> tree;
    vector<int> roots; 
    T E; // Neutral element

    PersistentSegTree(int size, int qry, T neutral = T()) : n(size), E(neutral) {
        int m = 2 + 4 * n + (__lg(n) + 2) * qry;
        tree.reserve(m);
        roots.reserve(qry + 2);
        
        tree.emplace_back(E);
        roots.emplace_back(0); // Dummy Version 0
    }

    int cloneNode(int v) {
        tree.emplace_back(tree[v]);
        return tree.size() - 1;
    }

    int build(int l, int r, const vector<long long>& a) {
        if (l == r) {
            tree.emplace_back(T(a[l]));
            return tree.size() - 1;
        }
        int v = tree.size();
        tree.emplace_back(E); // Placeholder
        
        int mid = l + (r - l) / 2;
        int lc = build(l, mid, a);
        int rc = build(mid + 1, r, a);
        
        // Merge math, then re-attach structural links
        tree[v] = merge(tree[lc], tree[rc]);
        tree[v].lc = lc;
        tree[v].rc = rc;
        return v;
    }

    void build_initial(const vector<long long>& a) {
        roots.emplace_back(build(0, n - 1, a)); 
    }

    int update(int prev_v, int l, int r, int idx, const T& val) {
        int v = cloneNode(prev_v);
        
        if (l == r) {
            tree[v] = val; // Triggers T's constructor
            tree[v].lc = tree[v].rc = 0;
            return v;
        }
        
        int mid = l + (r - l) / 2;
        
        idx <= mid ? tree[v].lc = update(tree[prev_v].lc, l, mid, idx, val) 
                   : tree[v].rc = update(tree[prev_v].rc, mid + 1, r, idx, val);
        
        // Merge math, then re-attach structural links
        int lc = tree[v].lc;
        int rc = tree[v].rc;
        tree[v] = merge(tree[lc], tree[rc]);
        tree[v].lc = lc;
        tree[v].rc = rc;
        
        return v;
    }

    T query(int v, int l, int r, const int& ql, const int& qr) {
        if (ql <= l && r <= qr) return tree[v];
        int mid = l + (r - l) / 2;        
        T qleft = (ql <= mid && tree[v].lc) ? query(tree[v].lc, l, mid, ql, qr) : E;
        T qright = (qr > mid && tree[v].rc) ? query(tree[v].rc, mid + 1, r, ql, qr) : E;
        return merge(qleft, qright);
    }

    void update(int ver, int idx, T val) {
        roots[ver] = update(roots[ver], 0, n - 1, idx, val);
    }

    T query(int ver, int ql, int qr) {
        return query(roots[ver], 0, n - 1, ql, qr);
    }

    void copy_version(int ver) {
        roots.emplace_back(roots[ver]); 
    }
};
// https://cses.fi/problemset/task/1737/
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; 
    cin >> n >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    // T = Node. E = Node(0)
    PersistentSegTree<Node> pst(n, q, Node(0));
    pst.build_initial(a);
    
    while (q--) {
        int type, ver;
        cin >> type >> ver;
        if (type == 1) {
            int a; long long x;
            cin >> a >> x;
            pst.update(ver, a - 1, Node(x));
        } else if (type == 2) {
            int l, r;
            cin >> l >> r;
            cout << pst.query(ver, l - 1, r - 1).val << '\n';
        } else {
            pst.copy_version(ver);
        }
    }
    
    return 0;
}
