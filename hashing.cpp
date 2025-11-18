const int mxn = 100005;
int pow1[mxn], pow2[mxn];
static const ll MOD1 = 1e9 + 7, MOD2 = 1e9 + 9, B1 = 43, B2 = 103;
class RollingHash {
	int n;
	vector<int> fwd1, fwd2, rev1, rev2;
public:
// B1, mod = (1949313259LL, 2091573227LL), (1997293877, 2117566807)
	RollingHash(const string &s) {
		n = s.size();
		fwd1.resize(n + 1, 0);
		fwd2 = rev1 = rev2 = fwd1;
		for (int i = 0; i < n; i++) {
			fwd1[i + 1] = (fwd1[i] * B1 + s[i]) % MOD1;
			fwd2[i + 1] = (fwd2[i] * B2 + s[i]) % MOD2;
		}
		for (int i = n - 1; i >= 0; i--) {
			rev1[i] = (rev1[i + 1] * B1 + s[i]) % MOD1;
			rev2[i] = (rev2[i + 1] * B2 + s[i]) % MOD2;
		}
	}
	// call with 0 index
	pair<int, int> getHash(int l, int r) {
		++r;
		int h1 = (fwd1[r] - (fwd1[l] * 1LL * pow1[r - l]) % MOD1 + MOD1) % MOD1;
		int h2 = (fwd2[r] - (fwd2[l] * 1LL * pow2[r - l]) % MOD2 + MOD2) % MOD2;
		return {h1, h2};
	}
	// call with 0 index
	pair<int, int> getReverseHash(int l, int r) {
		++r;
		ll h1 = (rev1[l] - (rev1[r] * 1LL * pow1[r - l]) % MOD1 + MOD1) % MOD1;
		ll h2 = (rev2[l] - (rev2[r] * 1LL * pow2[r - l]) % MOD2 + MOD2) % MOD2;
		return {h1, h2};
	}
};
int main() {
	for(int i=1;i<mxn;i++) {
    	pow1[i] = B1 * pow1[i-1] % MOD1;
    	pow2[i] = B2 * pow2[i-1] % MOD2;
  	}
  return 0;
}
