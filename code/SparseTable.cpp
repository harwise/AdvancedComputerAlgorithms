/*
 * Querys on
 * Some STATIC sequence (different from Segment Tree)
 * RMQ: range minimum query
 * 
 * Construction O(nlogn); Query O(1);
 */

#include <algorithm>

class SPT_RMQ
{
public:
   SPT_RMQ(int n, int A[])
   {
      for (int i = 0; i < n; i++) {
         A_[i] = A[i];
         Spt_[i][0] = i;   // 2^0 = 1
      }
      for (int j = 1; (1 << j) <= n; j++) {
         for (int i = 0; i + (1 << j) - 1 < n; i++) {
            Spt_[i][j] = std::min(Spt_[i][j-1],
                                  Spt_[i+(1<<(j-1))][j-1]);
         }
      }
   }

   int query(int i, int j)
   {
      int k = (int)floor(log((double)j-i+1)/log(2.0));     // 2^k <= (j-i+1)
      return std::min(Spt_[i][k],
                      Spt_[j-(1<<k)+1][k]);
   }

private:
   constexpr static int MAX_N = 1000;
   constexpr static int LOG_TWO_N = 10;   // 2^10 > 1000
   int A_[MAX_N];
   int Spt_[MAX_N][LOG_TWO_N];
};
