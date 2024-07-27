#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// link : https://atcoder.jp/contests/abc363/tasks/abc363_d
int main()
{
    ll n;
    cin >> n;
    if(n <= 10) return cout << --n, 0;
    n -= 2;
    ll P = 9;
    while(n >= P << 1) {
        n -= P << 1;
        P *= 10;
    }

    string ans = to_string(n % P + P / 9);
    cout << ans;
    if(n < P) ans.pop_back();
    reverse(ans.begin(), ans.end());
    cout << ans;
    return 0;
}