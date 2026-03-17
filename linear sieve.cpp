int spf[mxn];
int mu[mxn];
vector<int> prm;

mu[1] = 1;
for (int i = 2; i < mxn; ++i) {
	if (spf[i] == 0) {
		spf[i] = i;
		mu[i] = -1;
		prm.emplace_back(i);
	}
	for (int j = 0; i * prm[j] < mxn; ++j) {
		spf[i * prm[j]] = prm[j];
		if (prm[j] == spf[i]) {
			mu[i * prm[j]] = 0;
			break;
		}
		mu[i * prm[j]] = -mu[i];
	}
}
