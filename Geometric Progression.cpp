#include "bits/stdc++.h"
using namespace std;
using ll = long long;
// https://atcoder.jp/contests/abc293/tasks/abc293_e
// find sum of pow(A, i) for all 0 <= i < X modulo M
// X = 1e12, A, M = 1e9
int Mod;
// x >> 1 means x / 2
ll powMod(ll a, ll b) {
    ll ans = 1 % Mod;
    for (a %= Mod; b; a = a * a % Mod, b >>= 1)
        if (b & 1) ans=(ans*a)%Mod;
    return ans;
}
ll geoPro(ll a, ll b) {
    if(b == 1) return 1 % Mod;
    ll tem = geoPro(a, b >> 1) * (1 + powMod(a, b >> 1)) % Mod;
    if(b & 1) return (tem + powMod(a, b - 1)) % Mod;
    return tem;
}
signed main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    /*   tophhh   */
    ll A, X;
    cin >> A >> X >> Mod;
    if (A == 1)
        return cout << X % Mod, 0;

    cout << geoPro(A, X);

    return 0;
}
