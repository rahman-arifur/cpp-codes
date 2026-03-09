#include "bits/stdc++.h"
using namespace std;
// tophhh
namespace FFT {
  typedef complex<double> cd;
  const double PI = acos(-1);

  void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
      int bit = n >> 1;
      for (; j & bit; bit >>= 1) j ^= bit;
      j ^= bit;
      if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
      double ang = 2 * PI / len * (invert ? -1 : 1);
      cd wlen(cos(ang), sin(ang));
      for (int i = 0; i < n; i += len) {
        cd w(1);
        for (int j = 0; j < len / 2; j++) {
          cd u = a[i+j], v = a[i+j+len/2] * w;
          a[i+j] = u + v;
          a[i+j+len/2] = u - v;
          w *= wlen;
        }
      }
    }
    if (invert) {
      for (cd & x : a) x /= n;
    }
  }

  vector<long long> multiply(const vector<int> & a, const vector<int> & b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);
    vector<long long> result(n);
    for (int i = 0; i < n; i++) result[i] = round(fa[i].real());
    return result;
  }
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    string s; cin>>s;
    int n=s.size();
    vector<int> A(n), B(n);
    for(int i=0;i<n;i++) {
        if('A' == s[i]) A[i]=1;
        else B[n - i - 1] = 1;
    }
    auto res = FFT::multiply(A, B);
    for(int i=n;i<n+n-1;i++) cout << res[i] << '\n';
    // https://open.kattis.com/problems/kinversions
return 0;
  // if we keep holding onto yesterday, what are we going to be tomorrow?
}
