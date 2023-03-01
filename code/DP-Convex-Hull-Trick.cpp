/**
 * Author: Simon Lindholm
 * Date: 2017-04-20
 * License: CC0
 * Source: own work
 * Description: Container where you can add lines of the form kx+m, and query maximum values at points x.
 *  Useful for dynamic programming (``convex hull trick'').
 * Time: O(\log N)
 * Status: stress-tested
 */
#pragma once

#include <set>

using namespace std;

using ll = long long;

struct Line {
   mutable ll k, m, p;
   bool operator<(const Line& o) const { return k < o.k; }
   bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
   // (for doubles, use inf = 1/.0, div(a,b) = a/b)
   static const ll inf = LLONG_MAX;
   ll div(ll a, ll b) { // floored division
      return a / b - ((a ^ b) < 0 && a % b);
   }
   bool isect(iterator x, iterator y) {
      if (y == end()) return x->p = inf, 0;                    // 末尾的直线，没有下一条直线，没有交点；返回false。
      if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;       // 平行线，截距大的占主。
      else x->p = div(y->m - x->m, x->k - y->k);               // 交点的x值
      return x->p >= y->p;                                     // 根据交点的x值判断是否占主。
   }
   void add(ll k, ll m) {
      auto z = insert({ k, m, 0 }), y = z++, x = y;
      while (isect(y, z)) z = erase(z);                              // 删除被这条线占主的后边的线。
      if (x != begin() && isect(--x, y)) isect(x, y = erase(y));     // 删除这条刚刚新加的线。
      while ((y = x) != begin() && (--x)->p >= y->p)                 // 删除被这条线占主的前面的线。
         isect(x, erase(y));
   }
   ll query(ll x) {
      assert(!empty());
      auto l = *lower_bound(x);
      return l.k * x + l.m;
   }
};
