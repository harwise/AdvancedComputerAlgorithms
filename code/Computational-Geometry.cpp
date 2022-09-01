#include <algorithm>
#include <utility>
#include <stdio.h>
#include <cmath>
#include <numbers>

constexpr double EPS = (1e-9);

double DEG_to_RAD(double deg) {return deg * std::numbers::pi / 180;}

struct point_i {
   int x;
   int y;
};

struct point {
   double x;
   double y;
};

// useful for sort
bool operator < (const point& lhs, const point& rhs) {
   if (std::fabs(lhs.x - rhs.x) > EPS)
      return lhs.x < rhs.x;
   return lhs.y < rhs.y;
}

bool areSame(const point& p1, const point& p2) {
   return std::fabs(p1.x - p2.x) < EPS && fabs(p1.y - p2.y) < EPS;
}

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

double distToLine(const point& p, const point& line_a, const point& line_b, point& c) {
   // c = a + u * (a->b)
   vec ab = toVec(line_a, line_b);
   vec ap = toVec(line_a, p);

   double u = dot(ap, ab) / norm_sq(ab);
   c = translate(line_a, scale(ab, u));
   return dist(p, c);
}

double distToLineSegment(const point& p, const point& line_a, const point& line_b, point& c) {
   vec ab = toVec(line_a, line_b);
   vec ap = toVec(line_a, p);

   double u = dot(ap, ab) / norm_sq(ab);
   if (u < 0.0) {
      c = line_a;
      return dist(p, line_a);
   }
   if (u > 1.0) {
      c = line_b;
      return dist(p, line_b);
   }
   return distToLine(p, line_a, line_b, c);
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

