#include "bits/stdc++.h"
using namespace std;
using ll = long long;
template <typename T>
class SegmentTree {
private:
    // everything is 0 index
    vector<T> tree, arr;
    int n;
    function<T(T&,T&)> func; // merge function 
    // for sum, xor, min max etc

    T E; // when out of range what value to return
    // ex: if out of range for range minimum E=+inf
    // if xor E=0;
    void build(int nd, int st, int ed) {
        if (st == ed) return void(tree[nd] = arr[st]);
        int m = st+ed>>1, l=(nd<<1)|1, r=l+1;
        build(l, st, m);
        build(r, m + 1, ed);
        tree[nd] = func(tree[l], tree[r]);
    }

    void update(int nd, int st, int ed, int idx, T val) {
        if (st == ed) {
            arr[idx] = val;
            tree[nd] = val;
            return;
        }
        int m = st+ed>>1, l=(nd<<1)|1, r=l+1;
        if (idx <= m)
            update(l, st, m, idx, val);
        else
            update(r, m + 1, ed, idx, val);
        tree[nd] = func(tree[l], tree[r]);
    }

    T query(int nd, int st, int ed, int L, int R) {
        if (R < st || ed < L) return E;
        if (L <= st && ed <= R) return tree[nd];
        int m = st+ed>>1, l=(nd<<1)|1, r=l+1;
        T Lq = query(l, st, m, L, R);
        T Rq = query(r, m + 1, ed, L, R);
        return func(Lq, Rq);
    }

public:
    // array, null value, merge function
    SegmentTree(vector<T>& a, T nll, function<T(T&,T&)> ff) {
        func=ff; E=nll;
        swap(a,arr);
        n=arr.size();
        tree.resize(4 * n, E);
        build(0, 0, n - 1);
    }
    void update(int idx, T val) {
        update(0, 0, n - 1, idx, val);
    }
    T query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }
};
// min->nll=inf, mx->nll= -inf
// xor->nll=0, and->nll=LLONG_MAX(all bits set)
// take input as arr=vector<T>

// function<ll(ll&, ll&)> ff = [](ll& a, ll& b) {
//         return a+b;
// };
// SegmentTree<ll> sg(a, 0, ff);


// https://cses.fi/problemset/task/1648/

int main() {
    int n,q;cin>>n>>q;
    vector<ll> a(n);
    for(ll& i:a)cin>>i; 
    function<ll(ll&, ll&)> ff = [](ll& a, ll& b) {
        return a+b;
    };
    SegmentTree<ll> sg(a, 0, ff);
    for(int l,r,t,v;q--;) {
        cin>>t;
        if(t==1) {
            cin>>l>>v; l--;
            sg.update(l, v);
        }
        else {
            cin>>l>>r; l--, r--;
            cout<<sg.query(l,r)<<"\n";
        }
    }
    return 0;
}
