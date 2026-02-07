#include <bits/stdc++.h>
using namespace std;

struct SuffixArray {
	string S;
	vector<int> sa, rk, lcp;
	vector<vector<int>> st;
	vector<int> lg;
	int n, K, m = 256;

	SuffixArray(const string& s) : S(s) {
		build_sa();
		build_lcp();
		build_st();
	}

	void radix_sort(int limit, vector<int>& cnt, vector<int>& id) {
		fill(cnt.begin(), cnt.begin() + limit + 1, 0);
		for (int i = 0; i < n; ++i) cnt[rk[id[i]]]++;
		for (int i = 1; i <= limit; ++i) cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; --i) sa[--cnt[rk[id[i]]]] = id[i];
	}

	void build_sa() {
		int limit = m;
		n = S.length();
		sa.assign(n, 0);
		rk.assign(2 * n, -1);
		lcp.assign(n, 0);

		vector<int> cnt(max(n, limit) + 1), id(n);
		vector<int> oldrk(2 * n);

		for (int i = 0; i < n; ++i) rk[i] = S[i], id[i] = i;
		radix_sort(limit, cnt, id);

		for (int w = 1, p = 0; p < n; w <<= 1, limit = p) {
			p = 0;
			for (int i = max(0, n - w); i < n; ++i) id[p++] = i;
			for (int i = 0; i < n; ++i)
				if (sa[i] >= w) id[p++] = sa[i] - w;

			radix_sort(limit, cnt, id);

			oldrk = rk;
			p = 0;
			rk[sa[0]] = 0;
			for (int i = 1; i < n; ++i) {
				int u = sa[i], v = sa[i - 1];
				bool same = (oldrk[u] == oldrk[v]);
				if (same) {
					int r1 = (u + w < n) ? oldrk[u + w] : -1;
					int r2 = (v + w < n) ? oldrk[v + w] : -1;
					if (r1 != r2) same = false;
				}
				rk[sa[i]] = same ? p : ++p;
			}
			if (p == n - 1) break;
		}
	}

	void build_lcp() {
		for (int i = 0, k = 0; i < n; ++i) {
			if (rk[i] == 0) continue;
			if (k) k--;
			int j = sa[rk[i] - 1];
			while (i + k < n && j + k < n && S[i + k] == S[j + k]) k++;
			lcp[rk[i]] = k;
		}
	}

	void build_st() {
		lg.assign(n + 1, 0);
		for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
		K = lg[n] + 1;
		st.assign(n, vector<int>(K));
		for (int i = 0; i < n; i++) st[i][0] = lcp[i];
		for (int j = 1; j < K; j++)
			for (int i = 0; i + (1 << j) <= n; i++)
				st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
	}

	int get_lcp(int i, int j) {
		if (i == j) return n - i;
		int u = rk[i], v = rk[j];
		if (u > v) swap(u, v);
		u++;
		int k = lg[v - u + 1];
		return min(st[u][k], st[v - (1 << k) + 1][k]);
	}

	// -1 if S[l1..r1] < S[l2..r2], 0 if equal, 1 if greater
	int compareSubstrings(int l1, int r1, int l2, int r2) {
		int len1 = r1 - l1 + 1;
		int len2 = r2 - l2 + 1;
		int common = min({get_lcp(l1, l2), len1, len2});

		if (common == len1 && common == len2) return 0;	 // Equal
		if (common == len1) return -1; // S1 is prefix of S2 -> S1 < S2
		if (common == len2) return 1; // S2 is prefix of S1 -> S1 > S2

		// Character at 'common' differs
		return (S[l1 + common] < S[l2 + common]) ? -1 : 1;
	}

	// Finds range [L, R] in suffix array such that all suffixes in range start with pattern P
	// Returns pair {-1, -1} if not found
	pair<int, int> string_matching(const string& pat) {
		int pn = pat.size();
		int l = 0, r = n - 1, L = -1, R = -1;

		// Find Lower Bound
		while (l <= r) {
			int mid = l + (r - l) / 2;
			int res = S.compare(sa[mid], min(n - sa[mid], pn), pat);
			if (res >= 0) {
				L = mid;
				r = mid - 1;
			} else
				l = mid + 1;
		}

		if (L == -1 || S.compare(sa[L], min(n - sa[L], pn), pat) != 0) return {-1, -1};

		// Find Upper Bound
		l = L;
		r = n - 1;
		R = L;
		while (l <= r) {
			int mid = l + (r - l) / 2;
			int res = S.compare(sa[mid], min(n - sa[mid], pn), pat);
			if (res == 0) {
				R = mid;
				l = mid + 1;
			} else
				r = mid - 1;
		}
		return {L, R};
	}

	// Count occurrences of substring S[l..r]
	int count_occurence(int l, int r) {
		int len = r - l + 1;
		int idx = rk[l];
		int L_idx = idx, R_idx = idx;

		// Binary search left bound in SA
		int lo = 0, hi = idx;
		while (lo <= hi) {
			int mid = lo + (hi - lo) / 2;
			// query lcp between suffix at sa[mid] and suffix at sa[idx] (which is l)
			if (get_lcp(sa[mid], l) >= len) {
				L_idx = mid;
				hi = mid - 1;
			} else
				lo = mid + 1;
		}

		// Binary search right bound in SA
		lo = idx, hi = n - 1;
		while (lo <= hi) {
			int mid = lo + (hi - lo) / 2;
			if (get_lcp(sa[mid], l) >= len) {
				R_idx = mid;
				lo = mid + 1;
			} else
				hi = mid - 1;
		}
		return R_idx - L_idx + 1;
	}

	// Returns a vector where ans[k] is the number of distinct substrings of length k
	vector<long long> countDistinctByLength() {
		vector<long long> diff(n + 2, 0);
		for (int i = 0; i < n; i++) {
			// Suffix at sa[i] has length (n - sa[i])
			// It shares lcp[i] prefix with the previous sorted suffix sa[i-1]
			// So it contributes substrings of length (lcp[i] + 1) to (n - sa[i])
			int max_len = n - sa[i];
			int prev_match = (i == 0) ? 0 : lcp[i];

			if (max_len > prev_match) {
				diff[prev_match + 1]++;
				diff[max_len + 1]--;
			}
		}
		vector<long long> ans(n + 1, 0);
		long long curr = 0;
		for (int i = 1; i <= n; i++) {
			curr += diff[i];
			ans[i] = curr;
		}
		return ans;
	}
};

const int MAXN = 500005;
char buf[MAXN];

int main() {
	if (scanf("%s", buf) != 1) return 0;

	SuffixArray sa(buf);  // Constructor call

	int n = strlen(buf);
	for (int i = 0; i < n; ++i) {
		printf("%d%c", sa.sa[i], (i == n - 1 ? '\n' : ' '));
	}
	return 0;
}