#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const int mod = 1000000009;
using Mat = vector<vector<ll>>;
Mat matMul(Mat&a, Mat& b) {
    int n = a.size();
    int m = b[0].size(), s = b.size();
    Mat ret(n, vector<ll> (m, 0));
    for(int i=0;i<n;i++) {
        for(int k=0;k<s;k++) {
            if(a[i][k] == 0) continue;
            for(int j=0;j<m;j++) 
                (ret[i][j] += a[i][k] * b[k][j] % mod) %=mod;
        }
    }
    return ret;
}
Mat matPow(Mat a, ll b) {
    int n = a.size();
    Mat ret(n, vector<ll> (n, 0));
    for(int i=0;i<n;i++) ret[i][i]=1;
    for(;b;b>>=1, a=matMul(a,a)) if(b&1) ret = matMul(ret, a);
    return ret;
}
signed main() 
{
    cin.tie(0)->sync_with_stdio(0);
    ll n, m, c;cin>>n>>m>>c;
    ll F[n]; for(auto& i:F)cin>>i;
    if(m <= n) {
        cout<<F[--m];return 0;
    }
    Mat T(n, vector<ll>(n, 0));
    // Fn = a1*Fn-1 + a2*Fn-1 + a3*Fn-3 + ... + akFn-k n>=k
    // n * n matrix with first row being a1 .. ak
    // for the next n-1 rows make the box below the main diagonal = 1
    // n = 3
    /*
        Fn = 2*Fn-1 + 3*fn-2 + 4*fn-3
        i = 0 .. n-1 T[0][i] = ini[i] 
        i=1 .. n-1 T[i][i-1]=1;
        T = {
                2 3 4
                1 0 0
                0 1 0
            }
        
        let M[n][1] = {
                        Fn-1,
                        Fn-2,
                        ... ,
                        F0
                    }

        so final_matrix = T^(pow - N) * M
        ans = final_matrix[0] = Fn
    */
    for(int i=1;i<n;i++) {
        T[i][i-1]=1;
    }
    for(int i;c--;) {
        cin>>i;
        T[0][i-1]++;
    }
    // for(auto&i:T[0]) cout<<i<<' '; return 0;
    reverse(F,F+n);
    T = matPow(T, m-n);
    ll sum = 0;
    for(int i=0;i<n;i++) {
        (sum += T[0][i] * F[i] % mod) %= mod;
    }
    cout<<sum;
    return 0;
}
// https://vjudge.net/problem/Gym-100735B