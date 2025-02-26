int a[202020];
const int N=202020;
struct ST {
    #define lc (n << 1)
    #define rc ((n << 1) | 1)
	ll t[4 * N]{}, lazy[4 * N]{};
	void setup(int _n) {
        for(int i=0;i<4*_n;i++)t[i]=lazy[i]=0;
    }
	inline void push(int n, int b, int e) {
		if (lazy[n] == 0) return;
		t[n] = t[n] + lazy[n] * (e - b + 1);
		if (b != e) {
			lazy[lc] = lazy[lc] + lazy[n];
			lazy[rc] = lazy[rc] + lazy[n];
		}
		lazy[n] = 0;
	}
	inline ll combine(ll a,ll b) {
		return a + b;
	}
	inline void pull(int n) {
		t[n] = combine(t[lc], t[rc]);
	}
	void build(int n, int b, int e) {
		lazy[n] = 0;
		if (b == e) {
			t[n] = a[b];
			return;
		}
		int mid = (b + e) >> 1;
		build(lc, b, mid);
		build(rc, mid + 1, e);
		pull(n);
	}
	void upd(int n, int b, int e, int i, int j, ll v) {
		push(n, b, e);
		if (j < b || e < i) return;
		if (i <= b && e <= j) {
			lazy[n] = v;  // set lazy
			push(n, b, e);
			return;
		}
		int mid = (b + e) >> 1;
		upd(lc, b, mid, i, j, v);
		upd(rc, mid + 1, e, i, j, v);
		pull(n);
	}
	ll query(int n, int b, int e, int i, int j) {
		push(n, b, e);
		if(i>e || b>j) return 0;  // return null
		if (i<=b && e<=j) return t[n];
		int mid = (b + e) >> 1;
		return combine(query(lc, b, mid, i, j), query(rc, mid + 1, e, i, j));
	}
} segt;
