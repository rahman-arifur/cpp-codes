template <class T>
class segtree {// 0 based
private:
	int n;
	vector<T> tree, lazy;
	// change combine and push function
	T combine(T x, T y) {
		return min(x, y);
	}
	void push(int at, int l, int r) {
		if (lazy[at] == 0) return;
		tree[at] += lazy[at];
		if (l != r) {
      lazy[at << 1] += lazy[at];
      lazy[at << 1 | 1] += lazy[at];
    }
		lazy[at] = 0;
	}
	void build(vector<T> &arr, int at, int l, int r) {
    if (l == r) {
			tree[at] = arr[l];
			return;
		}
		int m = (l + r) >> 1;
		build(arr, at << 1, l, m);
		build(arr, at << 1 | 1, m + 1, r);
		tree[at] = combine(tree[at << 1], tree[at << 1 | 1]);
	}
	void update(int at, int l, int r, int L, int R, T val) {
    push(at, l, r);
		if (r < L || R < l) return;
		if (L <= l && r <= R) {
      lazy[at] += val;
			push(at, l, r);
			return;
		}
		int m = (l + r) >> 1;
		update(at << 1, l, m, L, R, val);
		update(at << 1 | 1, m + 1, r, L, R, val);
		tree[at] = combine(tree[at << 1], tree[at << 1 | 1]);
	}
  
	T query(int at, int l, int r, int L, int R) {
    push(at, l, r);
		if (L <= l && r <= R) return tree[at];
		int m = (l + r) >> 1;
		if (R <= m) return query(at << 1, l, m, L, R);
		if (m < L) return query(at << 1 | 1, m + 1, r, L, R);
		return combine(query(at << 1, l, m, L, R), query(at << 1 | 1, m + 1, r, L, R));
	}
public:
  T query(int l, int r) { return query(1, 0, n - 1, l, r); }	// Use this
  void update(int l, int r, T val) { update(1, 0, n - 1, l, r, val); }  // Use this
  segtree(int _n) {
    tree.resize(4 * _n, 2e9);
    lazy.resize(4 * _n, 0);
    n = _n;
  }
  void build(vector<T> &arr) { build(arr, 1, 0, n - 1); }	 // Use this
};
