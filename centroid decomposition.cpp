#include "bits/stdc++.h"
using namespace std;
// lca(a, b) in main tree = lca(a, b) in decomposed tree
// at most logN levels, O(nlogn)
#define mxn 200005
// tophhh
vector<int> adj[mxn];
int subsz[mxn], gone[mxn], epar[mxn];
int subdfs(int nd, int p = -1) {
  subsz[nd] = 1;
  for (int& ch : adj[nd]) {
    if (ch == p || gone[ch] != -1) continue;
    subsz[nd] += subdfs(ch, nd);
  }
  return subsz[nd];
}
int get_centroid(int nd, int tree_size, int p = -1) {
  for (int& ch : adj[nd]) {
    if (ch == p || gone[ch] != -1) continue;
    if (subsz[ch] * 2 > tree_size) {
      return get_centroid(ch, tree_size, nd);
    }
  }
  return nd;
}
void build_centroid(int nd, int sx, int p = -1) {
  int cntr = get_centroid(nd, subdfs(nd));
  if(-1 == p) p = cntr;
  // do something
  gone[cntr] = sx;
  epar[cntr] = p; // new tree construction
  for (int& ch : adj[cntr]) {
    if (gone[ch] != -1) continue;
    build_centroid(ch, sx + 1, cntr);
  }
}
void _init(int n) {
  for(int i=0; i<= n; i++) {
    subsz[i] = 0;
    gone[i] = -1;
    vector<int> ().swap(adj[i]);
  }
}
int main(){
  cin.tie(0)->sync_with_stdio(0);
  int n;cin>>n;
  _init(n);
  for(int i=1,u,v;i<n;i++) {
    cin>>u>>v;
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }
  build_centroid(1, 0);
  for(int i=1;i<=n;i++) cout<< char(gone[i] + 'A') << ' ';
return 0;
  // https://codeforces.com/contest/321/problem/C
}
