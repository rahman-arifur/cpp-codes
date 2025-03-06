#include <bits/stdc++.h>
using namespace std;
struct Hash {
    static const int M1=1e9+7, M2=1e9+9, B1=29, B2=31; // change mod and base accordingly, use prime numbers
    vector< pair<int, int> > hashes, expo;
    Hash(string& s) {
        int n = s.size();
        // hash array is 1 based
        hashes.assign(n+1, {0,0});
        expo.assign(n+1, {1,1});
        for(int i=0;i<n;i++) {
            hashes[i+1] = { ((1LL * hashes[i].first * B1 % M1) + s[i]) % M1 ,
                            ((1LL * hashes[i].second * B2 % M2) + s[i]) % M2 };
            expo[i+1] = { 1LL * expo[i].first * B1 % M1 ,
                            1LL * expo[i].second * B2 % M2 };
        }
    }

    // call with 0 based indexing
    pair<int, int> get(int l, int r) {
        ++l, ++r;
        int h1 = hashes[r].first - (1LL * hashes[l-1].first * expo[r-l+1].first % M1);
        ((h1%=M1)+=M1)%=M1;
        int h2 = hashes[r].second - (1LL * hashes[l-1].second * expo[r-l+1].second % M2);
        ((h2%=M2)+=M2)%=M2;
        return {h1, h2};
    }
};
