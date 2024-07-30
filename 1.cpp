array<ll, 3> extendedGCD(ll x, ll y) { // ret[0] = a, ret[1] = b, ret[2] = gcd
	if(0 == y) return {1, 0, x};
	array<ll, 3> ret = extendedGCD(y, x % y);
	swap(ret[0], ret[1]);
	ret[1] = ret[1] - x / y * ret[0];
	return ret;
}