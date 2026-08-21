#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    long long val;
    long long lazy_add;
    long long lazy_set;

    Node(long long v = 0, long long add = 0, long long set_val = 0) 
        : val(v), lazy_add(add), lazy_set(set_val) {}
    
    friend Node merge(const Node& a, const Node& b) {
        return Node(a.val + b.val); 
    }
    
    void apply(const Node& v, int st, int ed) {
        long long len = (ed - st + 1);
        
        // 1. If the incoming update is a SET operation
        if (v.lazy_set != 0) {
            val = v.lazy_set * len;
            lazy_set = v.lazy_set;
            lazy_add = 0; // Set completely overwrites any pending add
        }
        
        // 2. If the incoming update is an ADD operation
        if (v.lazy_add != 0) {
            val += v.lazy_add * len;
            // If we already have a pending set, just increase the set target
            if (lazy_set != 0) {
                lazy_set += v.lazy_add;
            } else {
                lazy_add += v.lazy_add;
            }
        }
    }
    
    // Push the current lazy tags down to the children
    void push_down(Node& left, Node& right, int st, int ed) {
        int mid = st + (ed - st) / 2;        
        if (lazy_set != 0) {
            left.apply(Node(0, 0, lazy_set), st, mid);
            right.apply(Node(0, 0, lazy_set), mid + 1, ed);
            lazy_set = 0;
        }
        if (lazy_add != 0) {
            left.apply(Node(0, lazy_add, 0), st, mid);
            right.apply(Node(0, lazy_add, 0), mid + 1, ed);
            lazy_add = 0;
        }
    }
};

template <typename T>
struct LazySegTree {
    int n;
    vector<T> tree;
    T E;

    LazySegTree(int _n, T neutral = T()) {
        n = _n;
        E = neutral;
        tree.assign(4 * n, E);
    }

    void build(const vector<T>& arr, int node, int st, int ed) {
        if (st == ed) {
            tree[node] = arr[st];
            return;
        }
        int mid = st + (ed - st) / 2;
        build(arr, node << 1, st, mid);
        build(arr, node << 1 | 1, mid + 1, ed);
        tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
    }

    void update(int node, int st, int ed, const int& L, const int& R, const T& val) {
        if (L <= st && ed <= R) {
            tree[node].apply(val, st, ed);
            return;
        }
        tree[node].push_down(tree[node << 1], tree[node << 1 | 1], st, ed);
        int mid = st + (ed - st) / 2;
        if (L <= mid) update(node << 1, st, mid, L, R, val);
        if (R > mid)  update(node << 1 | 1, mid + 1, ed, L, R, val);        
        tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
    }

    T query(int node, int st, int ed, const int& L, const int& R) {
        if (L <= st && ed <= R) return tree[node];
        tree[node].push_down(tree[node << 1], tree[node << 1 | 1], st, ed);
        int mid = st + (ed - st) / 2;
        T qleft = (L <= mid) ? query(node << 1, st, mid, L, R) : E;
        T qright = (R > mid) ? query(node << 1 | 1, mid + 1, ed, L, R) : E;
        return merge(qleft, qright);
    }

    void build(const vector<T>& arr) { build(arr, 1, 0, n - 1); }
    void update(int l, int r, const T& val) { update(1, 0, n - 1, l, r, val); }
    T query(int l, int r) { return query(1, 0, n - 1, l, r); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    
    vector<Node> initial_array(n);
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        initial_array[i] = Node(x);
    }
    
    LazySegTree<Node> st(n);
    st.build(initial_array);
    
    while (q--) {
        int type, a, b;
        cin >> type >> a >> b;
        a--; b--; // Convert to 0-based indexing for the tree
        
        if (type == 1) { // Add
            long long x; cin >> x;
            st.update(a, b, Node(0, x, 0)); // Pass x to the lazy_add parameter
        } else if (type == 2) { // Set
            long long x; cin >> x;
            st.update(a, b, Node(0, 0, x)); // Pass x to the lazy_set parameter
        } else if (type == 3) { // Query
            cout << st.query(a, b).val << "\n";
        }
    }
    
    return 0;
}
