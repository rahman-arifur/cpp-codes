
template <typename T>
class SegmentTree {
private:
	vector<T> tree, arr;
	int n;
    T E; // when out of range what value to return
    // ex: if out of range for range minimum E=+inf
    // if xor E=0;
    #define left(x) ((x << 1) | 1)
    #define right(x) ((x << 1) + 2)
	int mid(int l, int r) { return r + l >> 1; }
	T func(T a, T b) { 
		return a & b; // make it add, min, max, xor
	}
	void build(int nd, int st, int ed) {
		if (st == ed) return void(tree[nd] = arr[st]);
		int m = mid(st, ed);
		build(left(nd), st, m);
		build(right(nd), m + 1, ed);
		tree[nd] = func(tree[left(nd)], tree[right(nd)]);
	}

	void update(int nd, int st, int ed, int idx, T val) {
		if (st == ed) {
			arr[idx] = val;
			tree[nd] = val;
			return;
		}
		int m = mid(st, ed);
		if (idx <= m)
			update(left(nd), st, m, idx, val);
		else
			update(right(nd), m + 1, ed, idx, val);
		tree[nd] = func(tree[left(nd)], tree[right(nd)]);
	}

	T query(int nd, int st, int ed, int l, int r) {
		if (r < st || ed < l) return E;
		if (l <= st && ed <= r) return tree[nd];
		int m = mid(st, ed);
		T L = query(left(nd), st, m, l, r);
		T R = query(right(nd), m + 1, ed, l, r);
		return func(L, R);
	}

public:
	SegmentTree(const vector<T>& a, T E)
		: arr(a), E(E), n(a.size()) {
		tree.resize(4 * n, E);
		build(0, 0, n - 1);
	}
	void update(int idx, T val) {
		update(0, 0, n - 1, idx, val);
	}
    T query(int l, int r) {
		return query(0, 0, n - 1, l, r);
	}
};
