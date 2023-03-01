/*
 * Segment Tree
 * Interval Tree
 * Tournament Tree
 *
 * 1. Turning the **recursive pattern of Merge Sort** into a data structure.
 *    (Similar things: Divide and Conqure on Trees; Centroid Decomposition Trees)
 *    The advantage over Merge Sort is that we can store some extra info
 *    on the data structure. (e.g. store minimum value on every node/subtree.)
 * 
 * 2. Lazy Propagation. Store subtree information on every node.
 * 
 * 3. Stored in an array starting from index 1.
 *    The children of (i) is (2*i) and (2*i+1)
 * 
 * Querys on
 * Some DYNAMIC sequence
 * RMQ: range minimum query
 * 
 * Construction O(n); Query O(logn); Update O(logn)
 */

#include <vector>
#include <limits>

class SegmentTree
{
public:
   SegmentTree(int n)
      : _n(n),
        _lo(4*n + 1),      // more precise: 2 * (N round up to next power of 2)
        _hi(4*n + 1),      //               2 * 2^(floor(log2(N))+1)
        _delta(n),
        _min(n)
   {
      // root is index 1, including all items, i.e. [0, n-1]
      init(1, 0, n-1);
   }

   void init(int i, int a, int b)
   {
      _lo[i] = a;
      _hi[i] = b;

      if (a == b)
         return;

      int m = (a+b)/2;
      init(2*i, a, m);
      init(2*i+1, m+1, b);
   }

   void increment(int a, int b, int val)
   {
      increment(1, a, b, val);
   }

   int minimum(int a, int b)
   {
      return minimum(1, a, b);
   }

private:
   // propagation
   void prop(int i)
   {
      _delta[2*i] += _delta[i];
      _delta[2*i+1] += _delta[i];
      _delta[i] = 0;
   }

   void update(int i)
   {
      _min[i] = std::min(_min[2*i] + _delta[2*i],
                         _min[2*i+1] + _delta[2*i+1]);
   }

   void increment(int i, int a, int b, int val)
   {
      if (b < _lo[i] || _hi[i] < a)
         return;
      if (a <= _lo[i] && _hi[i] <= b) {
         _delta[i] += val;
         return;
      }
      // Partial cover cases
      prop(i);
      increment(2*i, a, b, val);
      increment(2*i+1, a, b, val);
      update(i);
   }

   int minimum(int i, int a, int b)
   {
      if (b < _lo[i] || _hi[i] < a)
         return std::numeric_limits<int>::max();
      if (a <= _lo[i] && _hi[i] <= b) {
         return _min[i] + _delta[i];
      }

      // Partial cover cases
      prop(i);
      int minLeft = minimum(2*i, a, b);
      int minRight = minimum(2*i+1, a, b);
      update(i);

      return std::min(minLeft, minRight);
   }

private:
   int _n;

   // The substree range
   /*
    * If we can give the [lo, hi] range when every method is called,
    * these two members can be removed.
    * That is easy because we just need the range of the root node. Every
    * call starts from the root.
    */
   std::vector<int> _lo;
   std::vector<int> _hi;

   // lazy propagation
   std::vector<int> _delta;

   // payload
   std::vector<int> _min;
};
