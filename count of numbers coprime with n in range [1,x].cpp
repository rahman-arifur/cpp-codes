using ll = long long;
vector<ll> primes{2};
const int mxn= 2e5+5;
void pre() {
    bool ok[mxn]{};
    for(ll i=3,j;i<mxn;i+=2)
        if(!ok[i]) {
            primes.push_back(i);
            for(j=i*i;j<mxn;j+=(i<<1)) ok[j]=1;
        }
}
vector<int> primeFactors(int n) {
    vector<int> pp;
    for (auto& p:primes) {
        if (n%p==0) {
            pp.push_back(p);
            while (n%p==0)n/=p;
        }
        else if(p*p>n)break;
    }
    if(n>1) pp.push_back(n);
    return pp;
}

// Function to count numbers in [1, x] that are coprime with n
int countCoprime(int x, int n) {
    if (n == 1) return x;
    auto pp = primeFactors(n);
    int k = pp.size();
    ll nonCoprime = 0;
    for (int mask = 1; mask < (1 << k); mask++) {
        ll mult = 1;
        int bits = 0;
        for (int i = 0; i < k; i++) {
            if (mask & (1 << i)) {
                mult *= pp[i];
                bits++;
            }
        }
        ll count = x / mult;
        if (bits % 2 == 1) nonCoprime += count;
        else nonCoprime -= count;
    }
    return x - nonCoprime;
}
