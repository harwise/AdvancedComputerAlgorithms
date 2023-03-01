/*
 * https://cp-algorithms.com/geometry/convex_hull_trick.html#problems
 * Assume you're given a set of functions such that each two can intersect at most once.
 * Let's keep in each vertex of a segment tree some function in such way,
 * that if we go from root to the leaf it will be guaranteed that one of the functions
 * we met on the path will be the one giving the minimum value in that leaf.
 *
 * Can be used to replace the Convex Hull Trick, if we only consider integers.
 */

#include <complex>
using namespace std;

namespace LiChaoTree
{
   typedef int ftype;
   typedef complex<ftype> point;
#define x real
#define y imag

   ftype dot(point a, point b) {
      return (conj(a) * b).x();
   }

   ftype f(point a, ftype x) {
      return dot(a, { x, 1 });
   }

   const int maxn = 2e5;

   // The segment tree should be initialized with default values, 0*x + inf.
   point line[4 * maxn];

   /*
    * 假设现在在[l，r]这个区间内，通过get方法都能获得最小值。
    * 加入nw之后，可能会在某些区间使nw成为最小值。所以要把nw从根节点到叶节点更新下去。
    *
    * 1.nw和原来的line，选择一个赋给当前节点。选择的是在中点上值更小的那个线A。
    * 2.区间分成左右两部分。nw和原来的line没有交点的那部分，不用更新，因为在此区间内，上一步的操作就能够保证能拿到最小值了。
    *   因为没有交点就意味着：中点值小即整个区间都小。
    * 3.另一个区间用B继续递归更新。因为如果A和B有交点，那在此区间上A不能完全替换B；在某些值上，B仍然可能成为最小值。
    *
    */
   void add_line(point nw, int v = 1, int l = 0, int r = maxn) {
      int m = (l + r) / 2;
      bool lef = f(nw, l) < f(line[v], l);      // 左端点，nw更小
      bool mid = f(nw, m) < f(line[v], m);      // 中间点，nw更小
      if (mid) {
         swap(line[v], nw);                     // 把nw赋予当前节点（整体上更低的直线）
      }                                         // 交点不在的那一半区域，求解的时候能够被这个直线覆盖到。
                                                // 交点所在的一般区域，需要比较这个直线和另一个直线的值，取min；
                                                // 所以后面会把另一条直线传下去处理。
      if (r - l == 1) {
         return;
      }
      else if (lef != mid) {                    // 交点在左半区域 - 递归处理左半区域
         add_line(nw, 2 * v, l, m);
      }
      else {                                    // 交点在右半区域
         add_line(nw, 2 * v + 1, m, r);
      }
   }

   /*
    * 从根节点往下走到叶节点，拿最小值。只要这个过程中，有任何一个节点出现了最小直线，就能够保证返回是正确的。
    */
   int get(int x, int v = 1, int l = 0, int r = maxn) {
      int m = (l + r) / 2;
      if (r - l == 1) {
         return f(line[v], x);
      }
      else if (x < m) {
         return min(f(line[v], x), get(x, 2 * v, l, m));
      }
      else {
         return min(f(line[v], x), get(x, 2 * v + 1, m, r));
      }
   }
}
