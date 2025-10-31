// https://atcoder.jp/contests/abc293/tasks/abc293_e
// find sum of pow(A, i) for all 0 <= i < X modulo M
// a^0 + a^1 + ... + a^x (under Mod m)
// X = 1e12, A, M = 1e9
int Mod;
ll powMod(ll a, ll b) {
    ll ans = 1 % Mod;
    for (a %= Mod; b; a = a * a % Mod, b >>= 1)
        if (b & 1) ans=(ans*a)%Mod;
    return ans;
}
/*
proof : 
		if(x is odd like 5)
			a^0 + a^1 + a^2 + a^3 + a^4 + a^5
		=   (a^0 + a^1 + a^2) +  a^3 * (a^0 + a^1 + a^2)
		= 	cur + a^(5 / 2 + 1) * cur

		else (x is even like 6)
			a^0 + a^1 + a^2 + a^3 + a^4 + a^5 + a^6
		=	sum(0 .. 5) + a^6
*/
int sum(ll x, int a) {
  if(x == 0) return 1 % Mod;
  if (x & 1) {
    ll p = x / 2;
    int cur = sum(p, a);
    return (cur + 1LL * powMod(a, p + 1) * cur % Mod) % Mod;
  }
  return (sum(x - 1, a) + powMod(a, x)) % Mod;
}
