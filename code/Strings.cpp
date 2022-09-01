#include <algorithm>
#include <utility>
#include <stdio.h>

using ii = std::pair<int, int>;

class kmp {
public:
   /*
    *     0 1 2 3 4 5 6 7 8 9 0 1 2 3
    *     S E V E N T Y   S E V E N
    * b  -1 0 0 0 0 0 0 0 0 1 2 3 4 5
    * 
    * b[i] 保存的是当p[i]不匹配的时候，应该从p中的哪个位置开始继续比较；所以
    *      它也对应于p[0..i-1]的最长前后缀。
    *      b[0]保存的是特殊值-1。从b一直往前找，当找到位置0，即p[0]也无法匹配的时候，
    *      就该从t的下一个位置和b从头开始比较了。
    *      b[m]也有值，即比p数组末尾多一个值。因为当全匹配之后，即b数组走到m，我们
    *      需要继续查找下一个匹配。
    */
   void kmpPreprocess() {
      int i = 0, j = -1;
      b_[0] = -1;
      while (i < m_) {
         while (j >= 0 && P_[i] != P_[j]) j = b_[j];     // if different
                                                         // j go back to the previous possible match
                                                         // until to b_[0] i.e. -1
         i++; j++;                                       // if same
                                                         // advance both pointers
         b_[i] = j;
      }
   }

   void kmpSearch() {
      int i = 0, j = 0;
      while (i < n_) {
         while (j >= 0 && T_[i] != P_[j]) j = b_[j];
         i++; j++;
         if (j == m_) {
            printf("P is found at index %d in T\n", i - j);
            j = b_[j];        // prepare j for the next possible match
         }
      }
   }

private:
   constexpr static int MAX_N = 100010;
   char T_[MAX_N];   // text
   char P_[MAX_N];   // pattern
   int b_[MAX_N];    // back table
   int n_;           // length of T
   int m_;           // length of P
};


class SuffixArray {
public:
   void countingSort(int k) {
      int i, sum, maxi = std::max(300, n_);
      memset(c_, 0, sizeof(c_));
      for (i = 0; i < n_; i++)
         c_[i+k < n_ ? RA_[i+k] : 0]++;
      for (i = sum = 0; i < maxi; i++) {
         int t = c_[i]; c_[i] = sum; sum += t;
      }
      for (i = 0; i < n_; i++) {
         int cInx = SA_[i] + k < n_ ? RA_[SA_[i] + k] : 0;
         tempSA_[c_[cInx]++] = SA_[i];
      }
      for (i = 0; i < n_; i++) {
         SA_[i] = tempSA_[i];
      }
   }

   // O(nlogn)
   void constructSA() {
      int i, k, r;
      for (i = 0; i < n_; i++) RA_[i] = T_[i] - '.';  // initial ranking
      for (i = 0; i < n_; i++) SA_[i] = i;            // initial SA
      for (k = 1; k < n_; k << 1) {
         countingSort(k);     // radix sort: sort based on the second item
         countingSort(0);     // (stable) sort based on the first item
         tempRA_[SA_[0]] = r = 0;   // re-ranking; start from rank r = 0
         for (i = 1; i < n_; i++) {
            tempRA_[SA_[i]] =       // compare adjacent suffixes
               (RA_[SA_[i]] == RA_[SA_[i-1]] &&
                RA_[SA_[i]+k] == RA_[SA_[i-1]+k])
               ? r
               : ++r;
         }
         for (i = 0; i < n_; ++i)
            RA_[i] = tempRA_[i];
      }
   }

   // O(mlogn)
   ii StringMatching(char* P, int m) {
      int lo = 0, hi = n_;
      while (lo < hi) {
         int mid = (lo + hi) / 2;
         int res = strncmp(T_ + SA_[mid], P, m);
         if (res >= 0) hi = mid;
         else lo = mid + 1;
      }
      if (strncmp(T_ + SA_[lo], P, m) != 0)
         return ii(-1, -1);
      ii ans; ans.first = lo;

      lo = 0; hi = n_;
      while (lo < hi) {
         int mid = (lo + hi) / 2;
         int res = strncmp(T_ + SA_[mid], P, m);
         if (res > 0) hi = mid;
         else lo = mid + 1;
      }
      ans.second = lo;
      return ans;
   }

   // O(n) Longest-Common-Prefix
   void ComputeLCP() {
      int i, L;
      Phi_[SA_[0]] = -1;
      for (i = 1; i < n_; i++)
         Phi_[SA_[i]] = SA_[i-1];
      for (i = L = 0; i < n_; i++) {
         if (Phi_[i] == -1) {
            PLCP_[i] = 0;
            continue;
         }
         while (T_[i + L] == T_[Phi_[i] + L])
            L++;
         PLCP_[i] = L;
         L = std::max(L-1, 0);
      }
      LCP_[0] = 0;
      for (i = 1; i < n_; i++)
         LCP_[i] = PLCP_[SA_[i]];
   }

private:
   constexpr static int MAX_N = 100010;     // at most 100K for O(nlogn)
   int n_;
   char T_[MAX_N];         // The input
   int RA_[MAX_N];         // Rank Array
   int tempRA_[MAX_N];
   int SA_[MAX_N];         // Suffix Array. item: the beginning index of the suffix.
   int tempSA_[MAX_N];
   int c_[MAX_N];          // counting/radix sort

   // for LCP
   int Phi_[MAX_N];        // [Positio Order Table] The previous suffix index in lexicographic order
   int PLCP_[MAX_N];       // [Positio Order Table] Permuted Longest-Common-Prefix
   int LCP_[MAX_N];        // [Lexicographic Order Table] The result: Longest-Common-Prefix
                           // The common prefix between consecutive suffixes.
};

