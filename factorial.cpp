ll qpow(ll a, ll b){ll ans=1;a%=mod;while(b>0){if(b&1)ans=(ans*a)%mod;a=(a*a)%mod;b>>=1;}return ans;}
int fac[mxn], invfac[mxn];
void pre(){
    fac[0]=1; ll i;
    for(i=1;i<mxn;i++) fac[i]=i*fac[i-1]%mod;
    i--;
    invfac[i] = qpow(fac[i], mod-2);
    for(--i;i>=0;i--) invfac[i]=(i+1)*invfac[i+1]%mod;
}
int nCr(int n, int r) {
    if(r<0 or r>n)return 0;
    return 1LL*fac[n]*invfac[n-r]%mod*invfac[r]%mod;
}
