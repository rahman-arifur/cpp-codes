#include "bits/stdc++.h"
using namespace std;
struct Point {
  typedef Point P;
  typedef long long T;
  T x, y;
  Point(T x=0, T y=0) : x(x), y(y) {}
  bool operator<(P& a)const{ return x==a.x?y<a.y:x<a.x; }
  bool operator==(P& a)const{ return x==a.x and y==a.y; }
  P operator-(P p) const { return P(x-p.x, y-p.y); }
  T dot(P p) const { return x*p.x + y*p.y; }
  T cross(P p) const { return x*p.y - y*p.x; }
  friend istream& operator>>(istream&in,P&p) {
    return in>>p.x>>p.y;
  }
};
vector<Point> convex_hull(vector<Point> points) {
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
    int n = points.size();
    if (n < 3) return points;
    vector<Point> hull;
    for (int i = 0; i < n; i++) {
        while (hull.size() >= 2 && (hull.back()-hull[hull.size()-2]).cross(points[i]-hull[hull.size()-2]) <= 0) 
            hull.pop_back();
        hull.push_back(points[i]);
    }
    int lower_size = hull.size();
    for (int i = n - 2; i >= 0; i--) {
        while (hull.size() > lower_size && (hull.back()-hull[hull.size()-2]).cross(points[i]-hull[hull.size()-2]) <= 0) 
            hull.pop_back();
        hull.push_back(points[i]);
    }
    hull.pop_back();
    return hull;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    for(cin>>n;n;cin>>n) {
        vector<Point> v(n);
        for(int i=0;i<n;i++)cin>>v[i];
        v = convex_hull(v);
        n = v.size();
        cout<<n<<'\n';
        // https://open.kattis.com/problems/convexhull
        for(int i=0;i<n;i++)cout<<v[i].x<<' '<<v[i].y<<'\n';
    }
}
