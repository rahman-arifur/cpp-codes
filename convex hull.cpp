#include <bits/stdc++.h>

using namespace std;

// Convex hull construction in O(n*log(n)): https://cp-algorithms.com/geometry/grahams-scan-convex-hull.html

struct point {
    int x, y;
};

bool isNotRightTurn(const point &a, const point &b, const point &c) {
    long long cross = (long long)(a.x - b.x) * (c.y - b.y) - (long long)(a.y - b.y) * (c.x - b.x);
    long long dot = (long long)(a.x - b.x) * (c.x - b.x) + (long long)(a.y - b.y) * (c.y - b.y);
    return cross < 0 || (cross == 0 && dot <= 0);
}

vector<point> convex_hull(vector<point> points) {
    sort(points.begin(), points.end(), [](auto& a, auto& b) { return a.x < b.x || (a.x == b.x && a.y < b.y); });
    int n = points.size();
    vector<point> hull;
    for (int i = 0; i < 2 * n - 1; i++) {
        int j = i < n ? i : 2 * n - 2 - i;
        while (hull.size() >= 2 && isNotRightTurn(hull.end()[-2], hull.end()[-1], points[j]))
            hull.pop_back();
        hull.push_back(points[j]);
    }
    hull.pop_back();
    return hull;
}
// returns the points
