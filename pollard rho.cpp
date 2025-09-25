#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(), x.end()
typedef long long ll;

namespace rho {
	ll mul(ll a, ll b, ll mod) {
		ll ret = a * b - mod * (ll)(1.L / mod * a * b);
		return ret + mod * (ret < 0) - mod * (ret >= (ll)mod);
	}

	ll bigMod(ll a, ll e, ll mod) {
		ll ret = 1;
		while (e) {
			if (e & 1) ret = mul(ret, a, mod);
			a = mul(a, a, mod);
			e >>= 1;
		}
		return ret;
	}
	bool isPrime(ll n) {
		if (n < 2 or n % 6 % 4 != 1) return (n | 1) == 3;
		ll a[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
		ll s = __builtin_ctzll(n - 1), d = n >> s;
		for (ll x : a) {
			ll p = bigMod(x % n, d, n), i = s;
			while (p != 1 and p != n - 1 and x % n and i--) p = mul(p, p, n);
			if ((p != n - 1) and i != s) return 0;
		}
		return 1;
	}
	ll pollard(ll n) {
		auto f = [&](ll x) { return mul(x, x, n) + 1; };
		ll x = 0, y = 0, t = 0, prod = 2, i = 1, q;
		while (t++ % 40 or gcd(prod, n) == 1) {
			if (x == y) x = ++i, y = f(x);
			if ((q = mul(prod, max(x, y) - min(x, y), n))) prod = q;
			x = f(x), y = f(f(y));
		}
		return gcd(prod, n);
	}
	vector<ll> factors(ll n) {	// return unsorted factors
		if (n == 1) return {};
		if (isPrime(n)) return {n};
		ll x = pollard(n);
		auto l = factors(x), r = factors(n / x);
		l.insert(l.end(), r.begin(), r.end());
		return l;
	}

};
vector<pair<ll, ll>> primes;

ll ans = -1, X;
void dfs(int i, ll cur, ll phi) {
	if (X / cur == phi) return void(ans = cur);
	if (i == primes.size()) return;
	dfs(i + 1, cur, phi);
	auto [p, cc] = primes[i];
	ll pw = 1;
	while (cc--) {
		pw *= p;
		ll newd = cur * pw;
		ll newp = phi * (pw / p) * (p - 1);
		dfs(i + 1, newd, newp);
	}
}
int main() {
	cin.tie(0)->sync_with_stdio(0);
	int t;
	cin >> t;
	while (t--) {
		ans = -1;
		cin >> X;
		// 2 * X = phi(n) * n
		if (X == 1) {
			cout << "2\n";
			continue;
		}
		X *= 2;
		auto prs = rho::factors(X);
		sort(all(prs));
		primes = {};
		for (int i = 0, j, m = prs.size(); i < m; i = j) {
			j = i;
			while (j < m and prs[i] == prs[j]) ++j;
			primes.emplace_back(prs[i], j - i);
		}
		dfs(0, 1, 1);
		cout << ans << '\n';
	}
	return 0;
}
// https://toph.co/p/find-the-primes