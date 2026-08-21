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

    SegmentTree(int _n, T neutral = T()) {
        n = 1;
        while (n < _n) n <<= 1; 
        E = neutral;
        tree.assign((n << 1) + 2, E); 
    }

    void update(int ind, const T& val) {
        ind += n;
        tree[ind] = val;
        for (ind >>= 1; ind > 0; ind >>= 1) {
            tree[ind] = merge(tree[ind << 1], tree[ind << 1 | 1]);
        }
    }

    T query(int l, int r) {
        T resL = E, resR = E;
        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) resL = merge(resL, tree[l++]);
            if (!(r & 1)) resR = merge(tree[r--], resR); 
        }
        return merge(resL, resR);
    }
};
