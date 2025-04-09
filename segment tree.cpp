template<typename T>
class SegmentTree {
private: // all 1 index
    int n;
    vector<T> tree;
    T E; // null value
    function<T(T&,T&)> func; // merge function 
public:
    SegmentTree (int _n, T init, function<T(T&,T&)> ff) {
        n = 1; E = init; func = ff;
        while (n < _n) n <<= 1;
        tree.resize(n<<1, E);
    }
    void update(int ind, T val) {
        ind += n;
        tree[ind] = val;
        while (ind > 1) {
            ind /= 2;
            tree[ind] = func(tree[ind<<1], tree[(ind<<1) |1]);
        }
    }
    T query(int l, int r) {
        T res = E;
        for (l+=n,r+=n;l<=r;l>>=1,r>>=1) {
            if (l&1) res = func(res, tree[l]);
            if (!(1&r)) res = func(res, tree[r]);
            ++l, --r;
        }
        return res;
    }
};
