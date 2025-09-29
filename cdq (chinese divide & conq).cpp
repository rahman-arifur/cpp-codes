#include "bits/stdc++.h"
using namespace std;
using ll = long long;
// https://www.spoj.com/problems/LIS2/
#define all(x) x.begin(), x.end()
struct point{
  int x,y,i;
  bool operator<(const point& o) const {
    return o.x!=x ? x<o.x : y<o.y;
  }
}a[100005];
int n, bit[100005], dp[100005];
void update(int i, int v) {
  for(;i<=n;i+=i&-i) bit[i]=max(v, bit[i]);
}
void clear(int i) {
  for(;i<=n;i+=i&-i) bit[i]=0;
}
int query(int i) {
  int r=0;for(;i>0;i-=i&-i) r=max(r, bit[i]); return r;
}
void CDQ(int L, int R) {
  if(R<=L) return;
  int M=L+R>>1;
  CDQ(L,M);
  vector<point> left; left.reserve(M-L+1); 
  for(int i=L;i<=M;i++) left.emplace_back(a[i]);
  vector<point> right; right.reserve(R-M); 
  for(int i=M+1;i<=R;i++) right.emplace_back(a[i]);
  sort(all(left));
  sort(all(right));
  int i=0;
  for(auto&pt:right) {
    while(i<left.size()&& left[i].x<pt.x) {
      update(left[i].y, dp[left[i].i]);
      ++i;
    }
    dp[pt.i] = max(dp[pt.i], 1 + query(pt.y-1));
  }
  for(auto&pp:left) clear(pp.y);
  CDQ(M+1,R);
}
main() {
	cin.tie(0)->sync_with_stdio(0);
	cin>>n;
  vector<int> v; v.reserve(n);
  for(int i=1;i<=n;i++) {
    cin>>a[i].x>>a[i].y; 
    a[i].i= i;
    v.emplace_back(a[i].y);
  }
  sort(all(v));
  v.erase(unique(all(v)), v.end());
  for(int i=1;i<=n;i++) {
    dp[i]=1;
    a[i].y = lower_bound(all(v), a[i].y) - v.begin() + 1;
  }
  CDQ(1, n);
  cout<<*max_element(dp,dp+1+n);
}
// if we keep holding onto yesterday, what are we going to be tomorrow?