#include "bits/stdc++.h"
using namespace std;
using ll = long long;
using ld = long double;
const ld PI = acosl(-1);
short sign(ll x) { return (x > 0) - (x < 0); }
struct PT {
  typedef PT P;
  typedef long double T;
  T x, y;
  PT(T x=0, T y=0) : x(x), y(y) {}
  bool operator<(P& p) const { return tie(x,y) < tie(p.x,p.y); }
  bool operator==(P& p) const { return tie(x,y)==tie(p.x,p.y); }
  P operator+(P& p) const { return P(x+p.x, y+p.y); }
  P operator-(P p) const { return P(x-p.x, y-p.y); }
  P operator*(T d) const { return P(x*d, y*d); }
  P operator/(T d) const { return P(x/d, y/d); }
  T dot(P p) const { return x*p.x + y*p.y; }
  T cross(P p) const { return x*p.y - y*p.x; }
  T cross(P a, P b) const { return (a-*this).cross(b-*this); }
  T dist2() const { return x*x + y*y; }
  ld dist() const { return sqrtl(dist2()); }
  // angle to x-axis in interval [-pi, pi]
  ld angle() const { return atan2l(y, x); }
  P unit() const { return *this/dist(); } // makes dist()=1
  P perp() const { return P(-y, x); } // rotates +90 degrees
  P normal() const { return perp().unit(); }
  // returns point rotated 'a' radians ccw around the origin
  P rotate(long double a) const {return P(x*cosl(a)-y*sinl(a),x*sinl(a)+y*cosl(a)); }
  friend ostream& operator<<(ostream& os, P p) {return os << p.x << ' ' << p.y << '\n';}
  friend istream& operator>>(istream&in,P&p) {return in>>p.x>>p.y;}
};
vector<PT> convex_hull(vector<PT> points) {
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
    int n = points.size();
    if (n < 3) return points;
    vector<PT> hull;
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
ld diameter(vector<PT>& v) {
    int n = v.size();
    if(n==1)return 0;
    if(n==2)return (v[0]-v[1]).dist();
    ld ans = 0;
    int i=0, j=1;
    while(i<n) {
        while((v[(i+1)%n]-v[i]).cross(v[(j+1)%n]-v[j])>=0) {
            ans = max(ans, (v[i]-v[j]).dist2());
            j=(j+1)%n;
        }
        ans = max(ans, (v[i]-v[j]).dist2());
        i++;
    }
    return sqrtl(ans);
}
signed main() 
{
    cin.tie(0)->sync_with_stdio(0);
    int n;cin>>n;
    vector<PT> v(n);
    for(auto& u:v)cin>>u;
    v = convex_hull(v);
    cout<<setprecision(20)<<diameter(v);
    return 0;
}
// https://open.kattis.com/problems/roberthood
