#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
template<typename T> using minHeap = priority_queue<T, vector<T>, greater<T>>;
using ll = long long; using pii = pair<int,int>;
const ll mxn = 200005, inf = 1LL << 60;
const ll mod1 = 1000000007, mod2 = 1000000009, B1 = 1007, B2 = 43;
// tophhh
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int subsz[mxn], rand_val[mxn];
vector<int> adj[mxn];
pii H[mxn];
void make_tree(int v, int p) {
    vector<pii> ch;
    subsz[v] = 1;
    for(int& u: adj[v]) if(u != p) {
        make_tree(u, v);
        subsz[v] += subsz[u];
        ch.emplace_back(H[u]);
    }
    // Sorting ensures isomorphism (order doesn't matter)
    sort(all(ch));
    // subtree hashing
    H[v] = {rand_val[subsz[v]], rand_val[subsz[v]]};
    for(auto& [f, s] : ch) {
        H[v].first = (H[v].first * B1 + f) % mod1;
        H[v].second = (H[v].second * B2 + s) % mod2;
    }
}
bool can(int v, int p) {
    vector<pair<pii, int>> has;
    for(int& u: adj[v]) if(u != p) {
        has.emplace_back(H[u], u);
    }
    sort(all(has));
    int tk = -1;
    for(int i=0;i<has.size();i++) {
        if(i + 1 < has.size() and has[i].first == has[i + 1].first) ++i;
        else if(tk != -1) return false;
        else tk = has[i].second; 
    }
    // If everything is paired, symmetry is perfect.
    if(-1 == tk) return true;
    // If one child is unpaired, the axis must continue through it.
    return can(tk, v);
}
// normally check symmetry(unordered) at the centroid
// if not rooted find the two centroids, then check 
void solve() {
    int n;cin>>n;
    for(int i=1;i<=n+1;i++) {
        vector<int> ().swap(adj[i]);
        rand_val[i] = uniform_int_distribution<int> (1, mod1)(rng);
    }
    for(int i=1,u,v;i<n;i++) {
        cin>>u>>v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    make_tree(1, 1);
    puts(can(1, 1) ? "YES" : "NO");
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int t;cin>>t;while(t--)
    solve();
return 0;
  // if we keep holding onto yesterday, what are we going to be tomorrow?
}
