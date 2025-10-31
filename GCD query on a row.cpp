#include "bits/stdc++.h"
using namespace std;
using ll = long long;
// https://codeforces.com/contest/1458/problem/A
// Row GCD
// given X, print gcd of (X + a1, X + a2, ... , X + an) for Q queries N < 100000
// gcd(x, y) = gcd(x - y, y)
ll GCD(ll a, ll b) {
	for (; b; a %= b, swap(a, b));
	return a;
}
signed main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	/*   tophhh   */
	int n, Q;
	ll G = 0, x, i;
	cin >> n >> Q;
	for (ll i = 0, k; i < n; i++) {
		cin >> k;
		if (i)
			G = GCD(G, abs(k - x));
		else
			x = k;
	}
	while (Q--) {
		cin >> i;
		cout << GCD(G, i + x) << ' ';
	}
	return 0;
}
