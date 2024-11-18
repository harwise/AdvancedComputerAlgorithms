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
#include <numeric>

using namespace std;

constexpr int MAXN = 5000;
constexpr int MAXK = 2000;

int x[MAXN + 10];

int values[MAXN + 10][MAXN + 10];

double Solve(int n, int mk)
{
   std::sort(x, x + n);

   //for (int i = 0; i < n; i++) {
   //   printf("%d ", x[i]);
   //}
   //printf("\n");

   for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j <= n; ++j) {
         values[i][j] = values[i][j - 1] + (x[j - 1] - x[i + (j - 1 - i) / 2]);
      }
   }

   std::vector<int> dp0(n + 1);
   std::vector<int> dp1(n + 1);
   std::vector<int> beginIndex0(n + 1);
   std::vector<int> beginIndex1(n + 1);

   for (int i = 0; i <= n; ++i) {
      dp1[i] = dp0[i] = values[0][i];
   }

   for (int k = 1; k < mk; ++k) {
      // k: we have k groups, and we want to generate the k+1 group.
      // 
      // We begin from x[k] as the beginning item.
      // try x[k], [x[k],x[k+1]], ...[x[k],x[k+1],...x[n-mk+k]]
      //
      // target: k+1 group
      // fill dp[k+1], ..., dp[n-mk+k+1].

      for (int p = k; p <= n - mk + k; ++p) {
         int begin = p, end = n - mk + k + 1;

         int leftItemR = 2 * x[p - 1] - x[(p - 1 + beginIndex0[p]) / 2];       // greater than this
         int rightItemR = 2 * x[p] - x[(p + beginIndex0[p]) / 2];              // smaller than this
         int beginC = std::lower_bound(x + p, x + end, leftItemR) - x;
         int endC = std::upper_bound(x + p, x + end, rightItemR) - x;

         begin = beginC * 2 - p;
         end = min(end, endC * 2 - p);

         for (int i = begin; i <= end; ++i) {
            int v = dp0[p] + values[p][i];
            if (v < dp1[i]) {
               dp1[i] = v;
               beginIndex1[i] = p;
            }
         }
      }

      //for (int i = 0; i < n; i++) {
      //   printf("%d ", beginIndex1[i]);
      //}
      //printf("\n");
      //for (int i = 0; i < n; i++) {
      //   printf("%d ", dp1[i]);
      //}
      //printf("\n");

      //for (int p = k; p <= n - mk + k; ++p) {
      //   int begin = p, end = n - mk + k + 1;

      //   for (int i = begin; i <= end; ++i) {
      //      int v = dp0[p] + values[p][i];
      //      if (v < dp1[i]) {
      //         dp1[i] = v;
      //         beginIndex1[i] = p;
      //      }
      //   }
      //}


      swap(dp0, dp1);
      swap(beginIndex0, beginIndex1);
   }

   return dp0[n];
}

double Solve2(int n, int mk)
{
   std::sort(x, x + n);

   std::vector<int> dp(n + 2);      // opt(i) of layer k
   std::vector<int> dp_1(n + 2);    // opt(i) of layer k-1
   std::vector<int> fk(n + 1);      // f(i) of layer k
   std::vector<int> fk_1(n + 1);    // f(i) of layer k-1

   for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j <= n; ++j) {
         values[i][j] = values[i][j - 1] + (x[j - 1] - x[i + (j - 1 - i) / 2]);
      }
   }

   // k = 1
   for (int i = 0; i <= n; ++i) {
      dp_1[i] = 0;
      fk_1[i] = values[0][i];
   }
   dp[n + 1] = dp_1[n + 1] = n;

   for (int k = 2; k <= mk; ++k) {
      for (int i = n; i >= k; --i) {
         fk[i] = std::numeric_limits<int>::max();
         for (int j = dp_1[i]; j <= dp[i + 1]; ++j) {
            int v = values[j][i];
            if (v + fk_1[j] < fk[i]) {
               fk[i] = v + fk_1[j];
               dp[i] = j;
            }
         }
      }
      std::swap(dp, dp_1);
      std::swap(fk, fk_1);
   }

   return fk_1[n];
}


int main() {
   int n, mk;
   scanf("%d%d", &n, &mk);
   for (int i = 0; i < n; i++) scanf("%d", x + i);

   //n = 20;
   //mk = 4;
   //while (1) {
   //   for (int i = 0; i < n; i++) {
   //      x[i] = rand() % 20;
   //   }
   //   double ans = Solve(n, mk);
   //   double ans2 = Solve2(n, mk);
   //   if (ans != ans2) {
   //      return -1;
   //   }
   //}

   //double ans = Solve(n, mk);
   double ans = Solve2(n, mk);

   printf("%.4lf\n", ans);
   return 0;
}
