ll cat[1001];
cat[0] = cat[1] = 1;
for (int i = 2; i <= 1000; i++) {
	auto& res = cat[i];
	for (int j = 0; j < i; j++)
		res += cat[j] * cat[i - j - 1],
			res %= Mod;
}
// cat(n) = nCr(2n, n) / (n + 1)
