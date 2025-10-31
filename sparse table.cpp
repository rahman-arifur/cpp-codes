int lg[mxn];
template <typename T>
class SparseTable {
	int n, LOG;
	vector<vector<T>> st;
	function<T(T&, T&)> merge;

public:
	SparseTable(const vector<T>& a, function<T(T&, T&)> f) : n(a.size()), merge(f) {
		LOG = 1;
		while ((1 << LOG) <= n) ++LOG;
		if (lg[2] == 0) {
			for (int i = 2; i < mxn; ++i)
				lg[i] = lg[i >> 1] + 1;
		}
		st.assign(LOG, vector<T>(n));
		st[0] = a;
		for (int j = 1; j < LOG; ++j) {
			int len = 1 << (j - 1);
			for (int i = 0; i + (1 << j) <= n; ++i) {
				st[j][i] = merge(st[j - 1][i], st[j - 1][i + len]);
			}
		}
	}

	// query on interval [l..r], 0-based
	T query(int l, int r) {
		int j = lg[r - l + 1];
		return merge(st[j][l], st[j][r - (1 << j) + 1]);
	}
};
