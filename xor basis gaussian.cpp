#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
// maximum subset xor
// https://www.spoj.com/problems/XMAX/
int main(){
  cin.tie(0)->sync_with_stdio(0);
  int n; cin>>n;
  const int B = 60;
  ll basis[B+1];
  memset(basis, -1, sizeof basis);
  for(ll a;n--;) {
    cin>>a;
    for(int i=B;i>=0;i--) if(a>>i&1) {
      if(basis[i] == -1) {
        basis[i] = a;
        break;
      }
      a ^= basis[i];
    }
  }
  ll ans = 0;
  for(int i=B;i>=0;i--) if(basis[i] != -1) {
    if(!(ans>>i&1)) ans ^= basis[i];
  }
  cout<<ans<<'\n';
  return 0;
}