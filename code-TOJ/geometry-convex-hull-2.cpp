#include <stdio.h>
#include <string.h>
#include <stack>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <queue>
#include <set>
#include <limits>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
   double x, y;

   Point Rotate(double rad) {
      return Point{x*cos(rad) - y*sin(rad),
                   x*sin(rad) + y*cos(rad)};
   }

   void Add(const Point &c) {
      x += c.x;
      y += c.y;
   }
};

Point AtoB(const Point& a, const Point& b) {
   return Point{ b.x - a.x, b.y - a.y };
}

bool operator < (const Point& l, const Point& r) {
   if (l.x < r.x) {
      return true;
   } else if (l.x > r.x) {
      return false;
   } else {
      return l.y < r.y;
   }
}

double Cross(const Point& a, const Point& b) {
   return a.x *b.y - b.x * a.y;
}

double Dist(const Point &a, const Point &b) {
   return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// 圆角矩形结构体
struct Rect {
   // 中心坐标
   Point c;
   // 倾斜角为 t rad
   double t;
};

// ================ 代码实现开始 ==================

// a, b, r: 所有圆角矩形的长、宽与圆角半径的长度
// rects: 所有圆角举行的列表
// 返回值：围住这些圆角矩形所用的非弹性绳的最短长度
double solve(double a, double b, double r, const vector<Rect> &rects) {

   Point rcPts[4] = {
      {a / 2 - r, b / 2 - r},
      {-a / 2 + r, b / 2 - r},
      {-a / 2 + r, -b / 2 + r},
      {a / 2 - r, -b / 2 + r}
   };

   std::vector<Point> points;
   for (auto &rc : rects) {
      for (int i = 0; i < 4; ++i) {
         Point pt = rcPts[i].Rotate(rc.t);
         pt.Add(rc.c);
         points.push_back(std::move(pt));
      }
   }

   sort(points.begin(), points.end());

   // upper
   std::vector<int> convex;
   for (int i = 0; i < points.size(); ++i) {
      while (convex.size() > 1) {
         int back = *convex.rbegin();
         int back2 = *(convex.rbegin() + 1);
         if (Cross(AtoB(points[back2], points[back]),
                   AtoB(points[back2], points[i]))> 0) {
            convex.pop_back();
         } else {
            break;
         }
      }
      convex.push_back(i);
   }

   // lower
   int base = convex.size();
   for (int i = points.size() - 2; i >= 0; --i) {
      while (convex.size() > base) {
         int back = *convex.rbegin();
         int back2 = *(convex.rbegin() + 1);
         if (Cross(AtoB(points[back2], points[back]),
                   AtoB(points[back2], points[i])) > 0) {
            convex.pop_back();
         } else {
            break;
         }
      }
      convex.push_back(i);
   }

   double ret = 0;
   for (int i = 0; i < convex.size() - 1; i++) {
      ret += Dist(points[convex[i]], points[convex[i + 1]]);
   }
   ret += 2 * atan(1) * 4 * r;

   return ret;
}

// ================ 代码实现结束 ==================

int main() {
   double a, b, r;
   scanf("%lf%lf%lf", &a, &b, &r);
   int n;
   scanf("%d", &n);
   vector<Rect> rects;
   for (int i = 0; i < n; i++) {
      double t;
      Point p;
      scanf("%lf%lf%lf", &p.x, &p.y, &t);
      rects.emplace_back(Rect{ p, t });
   }

   printf("%.2lf\n", solve(a, b, r, rects));

   return 0;
}
