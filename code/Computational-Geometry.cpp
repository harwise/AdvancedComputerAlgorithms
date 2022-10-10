#include <algorithm>
#include <utility>
#include <stdio.h>
#include <cmath>
#include <numbers>
#include <vector>

constexpr double EPS = (1e-9);

double DEG_to_RAD(double deg) {return deg * std::numbers::pi / 180;}

struct point_i {
   int x;
   int y;
};

struct point {
   double x, y;   // only used if more precision is needed
   point() { x = y = 0.0; }                      // default constructor
   point(double _x, double _y) : x(_x), y(_y) {}        // user-defined
   bool operator == (point other) const {
      return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
   }
   bool operator <(const point &p) const {
      return x < p.x || (abs(x - p.x) < EPS && y < p.y);
   }
};

double dist(const point& p1, const point& p2) {
   // hypotenuse: the longest side of a right triangle, opposite the right angle.
   return std::hypot(p1.x - p2.x, p1.y - p2.y);
}

// CCW
point rotate(const point& p, double theta) {
   double rad = DEG_to_RAD(theta);
   return {p.x * std::cos(rad) - p.y * std::sin(rad),
           p.x * std::sin(rad) + p.y * std::cos(rad)};
}

//-----------------------------------------------------------------------------

// ax + by + c = 0
struct line {
   double a;
   double b;
   double c;
};

void pointsToLine(const point& p1, const point& p2, line &l) {
   if (fabs(p1.x - p2.x) < EPS) {   // vertical line
      l.a = 1.0; l.b = 0; l.c = -p1.x;
   } else {
      l.a = (p1.y - p2.y) / (p1.x - p2.x);
      l.b = 1.0;
      l.c = (l.a * p1.x) - p1.y;
   }
}

bool areParallel(const line& l1, const line& l2) {
   return (fabs(l1.a - l2.a) < EPS) && (fabs(l1.b - l2.b) < EPS);
}

bool areSame(const line& l1, const line& l2) {
   return areParallel(l1, l2) && (fabs(l1.c - l2.c) < EPS);
}

bool areIntersect(const line& l1, const line& l2, point& p) {
   if (areParallel(l1, l1)) return false;
   p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
   // at least one line is not vertial line.
   if (fabs(l1.b) > EPS)
      p.y = -(l1.a * p.x + l1.c) / l1.b;
   else
      p.y = -(l2.a * p.x + l2.c) / l2.b;
   return true;
}

//-----------------------------------------------------------------------------

struct vec {
   double x;
   double y;
};

// p1->p2
vec toVec(const point& p1, const point& p2) {
   return {p2.x - p1.x, p2.y - p1.y};
}

vec scale(const vec& p, double s) {
   return {p.x * s, p.y * s};
}

point translate(const point& p, const vec& v) {
   return {p.x + v.x, p.y + v.y};
}

double dot(const vec& a, const vec& b) {
   return a.x * b.x + a.y * b.y;
}

double norm_sq(const vec &v) {
   return v.x * v.x + v.y * v.y;
}

double distToLine(const point& p, const point& A, const point& B, point& c) {
   // c = a + u * (a->b)
   vec ab = toVec(A, B);
   vec ap = toVec(A, p);

   double u = dot(ap, ab) / norm_sq(ab);
   c = translate(A, scale(ab, u));
   return dist(p, c);
}

double distToLineSegment(const point& p, const point& A, const point& B, point& c) {
   vec ab = toVec(A, B);
   vec ap = toVec(A, p);

   double u = dot(ap, ab) / norm_sq(ab);
   if (u < 0.0) {
      c = A;
      return dist(p, A);
   }
   if (u > 1.0) {
      c = B;
      return dist(p, B);
   }
   return distToLine(p, A, B, c);
}

// compute the intersection point between line segment p-q and line A-B
// p-q must cross the line
point lineIntersectSeg(const point& p, const point& q,
                       const point& A, const point& B) {
  double a = B.y-A.y, b = A.x-B.x, c = B.x*A.y - A.x*B.y;
  double u = fabs(a*p.x + b*p.y + c);     // the distance (scaled) from p to the line.
  double v = fabs(a*q.x + b*q.y + c);
  return point((p.x*v + q.x*u) / (u+v), (p.y*v + q.y*u) / (u+v));
}

// angle aob in rad
double angle(const point& a, const point& o, const point& b) {
   // oa dot ob = |oa| x |ob| x cos(theta)
   vec oa = toVec(o, a);
   vec ob = toVec(o, b);
   return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}

double cross(const vec& a, const vec& b) {
   return a.x * b.y - a.y * b.x;
}

bool ccw(const point &p, const point &q, const point &r) {
   return cross(toVec(p, q), toVec(q, r)) > 0;
}

bool collinear(const point &p, const point &q, const point &r) {
   return fabs(cross(toVec(p, q), toVec(q, r))) < EPS;
}

//-----------------------------------------------------------------------------

int insideCircle(const point_i &p, const point_i &c, int r) {
   int dx = p.x - c.x, dy = p.y - c.y;
   int Euc = dx * dx + dy * dy, rSq = r * r;
   return Euc < rSq ? 0 : Euc == rSq ? 1 : 2;      // inside/border/outside
}

// Determines the circle given two point2 on the circle and r.
bool circle2PtsRad(const point &p1, const point &p2, double r, point &c) {
   double d2 = (p1.x - p2.x) * (p1.x - p2.x) +
               (p1.y - p2.y) * (p1.y - p2.y);
   double det = r * r / d2 - 0.25;
   if (det < 0) return false;
   double h = std::sqrt(det);
   // one of the circles; the other can be get by reversing p1 and p2.
   c.x = (p1.x + p2.x) * 0.5 + (p1.y - p2.y) * h;
   c.y = (p1.y + p2.y) * 0.5 + (p2.x - p1.y) * h;
}

//----------------------------------------------------------------------------

double perimeter(double ab, double bc, double ca) {
   return ab + bc + ca;
}

// Heron's Formula. ab, bc, ca are the lengths of the sides.
double area(double ab, double bc, double ca) {
   double s = perimeter(ab, bc, ca) / 2.;
   double areaSq = s * (s - ab) * (s - bc) * (s - ca);
   return std::sqrt(areaSq);
}

// inscribed circle (incircle)
double rInCircle(double ab, double bc, double ca) {
   return area(ab, bc, ca) / (0.5 * perimeter(ab, bc, ca));
}

double rInCircle(const point& a, const point& b, const point& c) {
   return rInCircle(dist(a, b), dist(b, c), dist(c, a));
}

int inCircle(const point& p1, const point& p2, const point& p3, point& ctr, double& r) {
   r = rInCircle(p1, p2, p3);
   if (std::fabs(r) < EPS) return 0;

   line l1, l2;      // two angle bisectors

   // Angle Bisector Theorem: a/b = c/d. Easy to prove.
   double ratio = dist(p1, p2) / dist(p1, p3);
   point p = translate(p2, scale(toVec(p2, p3), ratio/(1+ratio)));
   pointsToLine(p1, p, l1);

   ratio = dist(p2, p1) / dist(p2, p3);
   p = translate(p1, scale(toVec(p1, p3), ratio/(1+ratio)));
   pointsToLine(p2, p, l2);

   areIntersect(l1, l2, ctr);
   return 1;
}

// circumscribed circle / circumcircle
double rCircumCircle(double ab, double bc, double ca) {
   return ab * bc * ca / (4.0 * area(ab, bc, ca));
}

double rCircumCircle(const point& a, const point& b, const point& c) {
   return rCircumCircle(dist(a, b), dist(b, c), dist(c, a));
}

/*
 * 方法1.
 * 约束条件：1、三点共面 2、三点到空间圆心坐标的距离相等。
 * 4个自由项4个方程可解，可以列出线性代数方程组，即可用消元法求解。
 * 方法2.
 * 利用已知三点确定两条线段，求两条线断的垂直平分线，计算出外接圆圆心坐标和半径。
 */
int circumCircle(const point& p1, const point& p2, const point& p3, point& ctr, double& r) {
   double a = p2.x - p1.x, b = p2.y - p1.y;
   double c = p3.x - p1.x, d = p3.y - p1.y;
   double e = a * (p1.x + p2.x) + b * (p1.y + p2.y);
   double f = c * (p1.x + p3.x) + d * (p1.y + p3.y);
   double g = 2.0 * (a * (p3.y - p2.y) - b * (p3.x - p2.x));
   if (fabs(g) < EPS) return 0;

   ctr.x = (d*e - b*f) / g;
   ctr.y = (a*f - c*e) / g;
   r = dist(p1, ctr);  // r = distance from center to 1 of the 3 points
   return 1;
}

// returns true if point d is inside the circumCircle defined by a,b,c
int inCircumCircle(point a, point b, point c, point d) {
  return (a.x - d.x) * (b.y - d.y) * ((c.x - d.x) * (c.x - d.x) + (c.y - d.y) * (c.y - d.y)) +
         (a.y - d.y) * ((b.x - d.x) * (b.x - d.x) + (b.y - d.y) * (b.y - d.y)) * (c.x - d.x) +
         ((a.x - d.x) * (a.x - d.x) + (a.y - d.y) * (a.y - d.y)) * (b.x - d.x) * (c.y - d.y) -
         ((a.x - d.x) * (a.x - d.x) + (a.y - d.y) * (a.y - d.y)) * (b.y - d.y) * (c.x - d.x) -
         (a.y - d.y) * (b.x - d.x) * ((c.x - d.x) * (c.x - d.x) + (c.y - d.y) * (c.y - d.y)) -
         (a.x - d.x) * ((b.x - d.x) * (b.x - d.x) + (b.y - d.y) * (b.y - d.y)) * (c.y - d.y) > 0 ? 1 : 0;
}

bool canFormTriangle(double a, double b, double c) {
   return (a + b > c) && (a + c > b) && (b + c > a);
}

// Law of Cosines
// c^2 = a^2 + b^2 - 2 * a * b * cos(angle_a_b)

// Law of Sines
// a / sin(alpha) = b / sin(beta) = c / sin(gamma)


//-----------------------------------------------------------------------------

// -Quadrilaterials
// rectangle
// square
// trapezium   梯形
// parallelogram  平行四边行
// kite
// rhombus  菱形


//-----------------------------------------------------------------------------

// P is a cw/ccw polygon and P[0] == P[n-1]
double perimeter(const std::vector<point> &P) {
   double result = 0.0;
   for (int i = 0; i < (int)P.size() - 1; i++)
      result += dist(P[i], P[i+1]);
   return result;
}

// P is a cw/ccw polygon and P[0] == P[n-1]
double area(const std::vector<point> &P) {
   double result = 0.0;
   for (int i = 0; i < (int)P.size() - 1; i++) {
      vec v1 = {P[i].x, P[i+1].y};
      vec v2 = {P[i].x, P[i+1].y};
      result += cross(v1, v2);
   }
   return std::fabs(result/2.0);
}

// P is a cw/ccw polygon and P[0] == P[n-1]
bool isConvex(const std::vector<point> &P) {
   int sz = (int)P.size();
   if (sz <= 3) return false;

   bool isLeft = ccw(P[0], P[1], P[2]);
   for (int i = 1; i < sz - 1; i++) {
      int i3 = ((i+2 == sz) ? 1: i+2);
      if (ccw(P[i], P[i+1], P[i3]) != isLeft)
         return false;
   }
   return true;
}

// P is a cw/ccw polygon and P[0] == P[n-1]
// convex or concave
// -1/0/1: inside/on/outside
int inPolygon(const point &pt, const std::vector<point> &P) {
   int n = (int)P.size();
   if (n <= 3)   return -1;

  for (int i = 0; i < n-1; ++i)                  // on vertex/edge?
    if (std::fabs(dist(P[i], pt) + dist(pt, P[i+1]) - dist(P[i], P[i+1])) < EPS)
      return 0;

   double sum = 0;
   for (int i = 0; i < (int)P.size() - 1; i++) {
      if (ccw(pt, P[i], P[i+1]))
         sum += angle(P[i], pt, P[i+1]);
      else
         sum -= angle(P[i], pt, P[i+1]);
   }

   // in: 360 degree; out: 0 degree.
   return std::fabs(sum) > std::numbers::pi ? 1 : -1;
}

// P is a cw/ccw polygon and P[0] == P[n-1]
// convex
// return the left side polygon
std::vector<point> cutPolygon(const point& A, const point& B,
                              const std::vector<point>& Q) {
   std::vector<point> P;
   for (int i = 0; i < (int)Q.size(); i++) {
      double left1 = cross(toVec(A, B), toVec(A, Q[i]));
      if (std::abs(left1) < EPS) {     // Q[i] is on the line.
         P.push_back(Q[i]);
         continue;
      }

      double left2 = 0;
      if (i != (int)Q.size() - 1) {
         left2 = cross(toVec(A, B), toVec(A, Q[i+1]));
      }

      if (left1 * left2 < -EPS) {   // edge(Q[i], Q[i+1]) cross the line
         P.push_back(lineIntersectSeg(Q[i], Q[i+1], A, B));
      }
   }
   if (!P.empty() && !(P.back() == P.front()))
      P.push_back(P.front());                      // wrap around

   return P;
}

/*
 * Convecx Hull.
 * 1) Contains all points.
 * 2) The area is maximized.
 * 3) The circumference is minmized.
 */
// CH: Convex Hull;
// Graham Scan. O(nlogn).
std::vector<point> CH_Graham(std::vector<point> &Pts) {
   std::vector<point> P(Pts);
   int n = (int)P.size();
   if (n <= 3) {
      if (!(P[0] == P[n - 1])) {
         P.push_back(P[0]);
      }
      return P;
   }

   // first, find P0 = point with lowest Y and if tie: rightmost X
   int P0 = std::min_element(P.begin(), P.end()) - P.begin();
   std::swap(P[0], P[P0]);

   // second, sort points by angle around P0, O(n log n) for this sort
   std::sort(++P.begin(), P.end(), [&P](const point &a, const point &b) {
      // 如果有conlinear的情况出现，需要注意在同一条线上的点要正确排序：
      // * 右半部分：按照y坐标从小到大。
      // * 左半部分：按照y坐标从大到小。
      return ccw(P[0], a, b);
      });

   // third, the ccw tests, although complex, it is just O(n)
   std::vector<point> S = {P[n-1], P[0], P[1]};
   int i = 2;
   while (i < n) {
      int j = (int)S.size() - 1;
      if (ccw(S[j-1], S[j], P[i]))
         S.push_back(P[i++]);
      else
         S.pop_back();
   }
   return S;
}

// CH: Convex Hull;
// O(nlogn)
std::vector<point> CH_Andrew(std::vector<point> &Pts) {
   int n = (int)Pts.size(), k = 0;
   std::vector<point> P(Pts);
   sort(P.begin(), P.end());                  // sort the points by x/y
   std::vector<point> H(2 * n);

   for (int i = 0; i < n; ++i) {                  // build lower hull
      while ((k >= 2) && !ccw(H[k - 2], H[k - 1], P[i])) --k;
      H[k++] = P[i];
   }

   for (int i = n - 2, t = k + 1; i >= 0; --i) {       // build upper hull
      while ((k >= t) && !ccw(H[k - 2], H[k - 1], P[i])) --k;
      H[k++] = P[i];
   }
   H.resize(k);
   return H;
}

// CH: Convex Hull;
// Jarvis March. O(nh) where h is the count of the result points.
std::vector<point> CH_Jarvis(std::vector<point> &Pts) {
   /*
    * 1. start from the point with the lowest Y coordinate.
    * 2. go through all the left points, to find the one with the smallest ccw.
    * 3. repeat until reaching the starting point.
    */
}

/*
 * Great - Circle Distance.Given two points on Earth(latitude & longitude),
 * get the shortest distance along a path on the surface of the sphere.
 */
double gcDistance(double pLat, double pLong,
                  double qLat, double qLong,
                  double radius)
{
   pLat = DEG_to_RAD(pLat);
   pLong = DEG_to_RAD(pLong);
   qLat = DEG_to_RAD(qLat);
   qLong = DEG_to_RAD(qLong);
   return radius * acos(cos(pLat)*cos(pLong)*cos(qLat)*cos(qLong) +
                        cos(pLat)*sin(pLong)*cos(qLat)*sin(qLong) +
                        sin(pLat)*sin(qLat));
}
