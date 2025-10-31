// this question answers how many characters u need to insert to make string S a palindrome
// so we do suze(S) - (longest palindromic subsequence) as the answer
int solve() {
	string s;
	cin >> s;
	int n = size(s);
	vector dp(n + 1, vector<int>(n + 1, -1));
	// this function calculates the longest palindromic subsequence in a string in range i ... j
	function<int(int, int)> mem = [&](int i, int j) -> int {
		if (i == j) return dp[i][j] = 1;
		if (-1 != dp[i][j]) return dp[i][j];
		if (j == i + 1 and s[i] == s[j])
			return dp[i][j] = 2;
		if (s[i] == s[j])
			return dp[i][j] = 2 + mem(i + 1, j - 1);
		return dp[i][j] = max(mem(i + 1, j), mem(i, j - 1));
	};
	return n - mem(0, n - 1);
}
