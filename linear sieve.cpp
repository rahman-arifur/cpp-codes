int spf[mxn];
vector<int> prm;
for (int i = 2; i < mxn; ++i) {
	if (spf[i] == 0) {
		spf[i] = i;
		prm.emplace_back(i);
	}
	for (int j = 0; i * prm[j] < mxn; ++j) {
		spf[i * prm[j]] = prm[j];
		if (prm[j] == spf[i]) {
			break;
		}
	}
}
