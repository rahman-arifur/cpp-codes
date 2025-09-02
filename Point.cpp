#include "bits/stdc++.h"
using namespace std;
using ll = long long;
using ld = long double;
const ld PI = acosl(-1);
template <class T=ll> int sign(T x) { return (x > 0) - (x < 0); }
template<class T=ll>
struct Point {
  typedef Point P;
  T x, y;
  explicit Point(T x=0, T y=0) : x(x), y(y) {}
  bool operator<(P& p) const { return tie(x,y) < tie(p.x,p.y); }
  bool operator==(P& p) const { return tie(x,y)==tie(p.x,p.y); }
  P operator+(P& p) const { return P(x+p.x, y+p.y); }
  P operator-(P& p) const { return P(x-p.x, y-p.y); }
  P operator*(T d) const { return P(x*d, y*d); }
  P operator/(T d) const { return P(x/d, y/d); }
  T dot(P& p) const { return x*p.x + y*p.y; }
  T cross(P& p) const { return x*p.y - y*p.x; }
  T cross(P& a, P& b) const { return (a-*this).cross(b-*this); }
  T dist2() const { return x*x + y*y; }
  ld dist() const { return sqrtl(dist2()); }
  // angle to x-axis in interval [-pi, pi]
  ld angle() const { return atan2l(y, x); }
  P unit() const { return *this/dist(); } // makes dist()=1
  P perp() const { return P(-y, x); } // rotates +90 degrees
  P normal() const { return perp().unit(); }
  // returns point rotated 'a' radians ccw around the origin
  P rotate(long double a) const {
    return P(x*cosl(a)-y*sinl(a),x*sinl(a)+y*cosl(a)); }
  friend ostream& operator<<(ostream& os, P p) {
    return os << "(" << p.x << "," << p.y << ")"; }
  friend istream& operator>>(istream&in,P&p) {
    return in>>p.x>>p.y;
  }
};
ld pt_to_seg_mindis(Point<ll>& pt, Point<ll>& a, Point<ll>& b) {
    Point ab = b - a;
    Point ap = pt - a;
    auto bp = pt - b;
    auto ba = a- b;
    if(ab.dot(ap) < 0) return ap.dist();
    else if(ba.dot(bp)<0) return bp.dist();
    else return fabsl(ap.cross(ab))/ab.dist();
}
