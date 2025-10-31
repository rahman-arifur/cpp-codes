// u can also precalculate all the primes in a vector then use the loop for (int& p:primes) if(n%p==0) like this
vector<int> primes{2};
bool prm[Maxn];
void pre() {
	ll i, j;
	for (i = 4; i < Maxn; i += 2) prm[i] = true;
	for (i = 3; i < Maxn; i += 2)
		if (!prm[i]) {
			primes.push_back(i);
			for (j = i * i; j < Maxn; j += (i << 1))
				prm[i] = true;
		}
}
ll numberOfDivisors(ll num) {
	int total = 1;
	for (int i = 2; 1ll * i * i <= num; i++) {
		if (num % i == 0) {
			int e = 0;
			do {
				e++;
				num /= i;
			} while (num % i == 0);
			total *= e + 1;
		}
	}
	if (num > 1)
		total *= 2;
	return total;
}

ll SumOfDivisors(ll num) {
	ll total = 1;
	for (int i = 2; 1ll * i * i <= num; i++) {
		if (num % i == 0) {
			int e = 0;
			do {
				e++;
				num /= i;
			} while (num % i == 0);

			ll sum = 0, pow = 1;
			do {
				sum += pow;
				pow *= i;
			} while (e-- > 0);
			total *= sum;
		}
	}
	if (num > 1)
		total *= (1 + num);
	return total;
}
