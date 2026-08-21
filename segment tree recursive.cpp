struct Node {
    long long val;
    
    Node(long long v = 0) : val(v) {}
    
    friend Node merge(const Node& a, const Node& b) {
        return Node(a.val + b.val); 
    }
};

template <typename T>
struct SegmentTree {
    int n;
    vector<T> tree;
    T E;

    SegmentTree(int n, T neutral = T()) {
        this->n = n;
        E = neutral;
        tree.assign(4 * n, E);
    }

    void update(int node, int st, int ed, const int& idx, const T& val) {
        if (st == ed) {
            tree[node] = val; 
            return;
        }
        int mid = st + (ed - st) / 2;
        idx <= mid ? update(node << 1, st, mid, idx, val) 
                   : update(node << 1 | 1, mid + 1, ed, idx, val);
        tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
    }

    T query(int node, int st, int ed, const int& l, const int& r) {
        if (l <= st && ed <= r) return tree[node];
        int mid = st + (ed - st) / 2;
        T qleft = (l <= mid) ? query(node << 1, st, mid, l, r) : E;
        T qright = (r > mid) ? query(node << 1 | 1, mid + 1, ed, l, r) : E;
        return merge(qleft, qright);
    }

    void update(int idx, T val) { update(1, 0, n - 1, idx, val); }
    T query(int l, int r) { return query(1, 0, n - 1, l, r); }
};
