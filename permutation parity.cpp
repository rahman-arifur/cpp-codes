bool parity(const vector<int> &p) {
    int n = p.size();
    if (n == 1) return false;
    vector<int> cur(n);
    vector<int> inv_cur(n);
    iota(cur.begin(), cur.end(), 0);
    iota(inv_cur.begin(), inv_cur.end(), 0);
    auto do_cycle = [&](int i, int j, int k) {
        int tmp = cur[k];
        cur[k] = cur[j];
        cur[j] = cur[i];
        cur[i] = tmp;

        inv_cur[cur[i]] = i;
        inv_cur[cur[j]] = j;
        inv_cur[cur[k]] = k;
    };
    for (int i = 0; i < n - 2; i++) {
        if (cur[i] != p[i]) {
            int j = inv_cur[p[i]];
            if (j != n - 1) {
                do_cycle(n - 1, j, i);
            } else {
                do_cycle(n - 2, j, i);
            }
        }
    }
    return cur[n - 1] != p[n - 1];
}
