#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
typedef long long ll;
// https://www.spoj.com/problems/MIFF/
ll mod, N;
ll qpow(ll a, ll b) {
  ll r=1; a%=mod; if(a<0) a+= mod;
  for(;b;b>>=1,a=a*a%mod) if(1&b) r=r*a%mod;
  return r;
}
// tophhh
bool singular(vector<vector<ll>>&A) {
  for(ll col=0;col<N;col++) {
    ll mxr = col;
    for(ll ro=col+1;ro<N;ro++) {
      if(A[mxr][col]<A[ro][col]) mxr = ro;
    }
    if(mxr == col and A[mxr][col]==0) return true;
    swap(A[mxr], A[col]);
    ll inv = qpow(A[col][col], mod - 2);
    for(ll i=col;i<2*N;i++) (A[col][i] *= inv) %= mod;
    for(ll r=0;r<N;++r) if (r!=col) {
      ll gun=A[r][col];
      if(gun==0)continue;
      for(ll j=0;j<2*N;++j) {
        A[r][j]=(A[r][j]-gun*A[col][j])%mod;
        if(A[r][j]<0)A[r][j]+=mod;
      }
    }
  }
  return false;
}
signed main(){
  cin.tie(0)->sync_with_stdio(0);
  for(cin>>N>>mod;N+mod;cin>>N>>mod) {
    vector<vector<ll>> A(N, vector<ll>(N+N, 0));
    for(ll i=0;i<N;i++) {
      for(ll j=0;j<N;j++) {
        cin>>A[i][j]; A[i][j] %= mod;
        if(A[i][j]<0) A[i][j] += mod;
      }
      A[i][N+i]=1%mod;
    }
    if(!singular(A)) {
      for(ll i=0;i<N;i++) {
        for(ll j=0;j<N;j++) {
          cout<<A[i][j+N]%mod<<' ';
        }
        cout<<'\n';
      }
    } else cout<<"singular\n";
    cout<<'\n';
  }
  return 0;
  // if we keep holding onto yesterday, what are we going to be tomorrow?
}
