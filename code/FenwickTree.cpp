/*
 * Fenwick Tree
 * Binary Indexed Tree
 *
 * Querys on
 * Some DYNAMIC sequence
 * Determine range sum
 *
 * Baseline: O(n)
 *
 * Prefix Sum Solutin: query O(1); update O(n).
 *
 * Fenwick Tree manages prefix sums in a smart way. Query O(logn); Update O(logn)
 * 
 * 1,    2,    3,    4,    5,    6
 * 0001, 0010, 0011, 0100, 0101, 0110
 * <-|         <-|         <-|
 * <-----|                 <-----|
 * <-----------------|
 * 
 * The lowest one bit is import. It decides how many slots it covers.
 * Query: sum of prefix sums.
          The count of bit 1 is how many prefix sums are taken.
 * Update: doulbe the lowest bit 1 until overflow.
           The count of bit 0 is the loop count (how many prefix sums are updated).
 */

#include <vector>

class BIT
{
public:
   BIT(int sz)
      : _table(sz + 1)
   {
   }

   void Update(int i, int delta)
   {
      while (i < (int)_table.size()) {
         _table[i] += delta;
         i += (i & -i);
      }
   }

   // [1, i]
   int sum(int i)
   {
      int ret = 0;
      while (i > 0) {
         ret += _table[i];
         i -= (i & -i);
      }
      return ret;
   }

   // [i, j]
   int rangeSum(int i, int j)
   {
      return sum(j) - sum(i - 1);
   }

private:
   std::vector<int> _table;
};


