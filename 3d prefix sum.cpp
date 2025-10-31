// https://atcoder.jp/contests/abc366/tasks/abc366_d
// cuboid sum query
void solve() {
	int n, q;
	cin >> n;
	vector a(n, vector(n, vector(n, 0LL)));
	for (auto& g1 : a) {
		for (auto& g2 : g1) {
			for (auto& el : g2) {
				cin >> el;
			}
		}
	}

	vector pref(n + 1, vector(n + 1, vector(n + 1, (ll)0)));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < n; ++k) {
				pref[i + 1][j + 1][k + 1] = pref[i + 1][j + 1][k] + pref[i + 1][j][k + 1]
				   + pref[i][j + 1][k + 1] - pref[i + 1][j][k] - pref[i][j + 1][k]
				   - pref[i][j][k + 1] + pref[i][j][k] + a[i][j][k];
			}
		}
	}
	cin >> q;
	while (q--) {
		int lx, rx, ly, ry, lz, rz;
		cin >> lx >> rx >> ly >> ry >> lz >> rz;
		--lx;
		--ly;
		--lz;

		int ans = pref[rx][ry][rz];

		ans -= pref[lx][ry][rz];
		ans -= pref[rx][ry][lz];
		ans -= pref[rx][ly][rz];

		ans += pref[rx][ly][lz];
		ans += pref[lx][ry][lz];
		ans += pref[lx][ly][rz];

		ans -= pref[lx][ly][lz];

		cout << ans << '\n';
	}
}