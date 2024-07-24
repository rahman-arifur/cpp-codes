#include "bits/stdc++.h"
using namespace std;
using ll=long long; 
vector<int> a;
vector<ll> tree;

int N,q;
void build(int i = 0) {
    for(;i < N; i++)
        tree[i + N] = a[i];
    for(i = N - 1; i; i--) 
        tree[i] = tree[i << 1] + tree[(i << 1) + 1];
}

ll query(int node, int left, int right, const int& queryL, const int& queryR) {
    if(left > queryR or right < queryL) return 0;
    if(queryL <= left and right <= queryR) return tree[node];
    int mid = (left + right) >> 1;
    return query(2 * node, left, mid, queryL, queryR) +
            query(2 * node + 1, mid + 1, right, queryL, queryR);
}

ll queryIterative(int L, int R) {
    ll sum = 0;
    for(L += N, R += N; L <= R; L >>= 1, R >>= 1) {
            if(L & 1) sum += tree[L++];
            if((R & 1) == 0) sum += tree[R--];
    }
    return sum;
}

void update(int pos, int val) {
    int i = N + pos;
    tree[i] = a[i - N] = val;
    for(i >>= 1; i; i >>= 1) 
        tree[i] = tree[i << 1] + tree[(i << 1) + 1];
}
signed main() 
{
    cin.tie(nullptr) -> sync_with_stdio(false);
    /*   tophhh   */
    cin >> N >> q;
    for(int i = 0, x; i < N; i++) {
        cin >> x;
        a.push_back(x);
    }

    while(__builtin_popcount(N) != 1) {
        ++N;
        a.push_back(0);
    }

    tree.resize(N << 1);
    build();

    int  L, R;
    while(q--) { 
        cin >> L >> R;
        --L, --R; 
        cout << 
        // query(1, 0, N - 1, L, R)
        queryIterative(L, R)
         << "\n"; 
    }
return 0;
}
