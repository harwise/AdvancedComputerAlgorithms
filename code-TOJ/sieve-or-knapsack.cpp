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

using namespace std;


constexpr int MAXN = 300;

int a[MAXN + 10];

int main() {
   int n;
   scanf("%d", &n);
   for (int i = 0; i < n; i++) scanf("%d", a + i);

   sort(a, a + n);

   std::vector<int> v;
   for (int i = 0; i < n; ++i) {
      if (a[i] == 0) continue;
      if (v.empty() || a[i] != v.back())
         v.push_back(a[i]);
      for (int j = i + 1; j < n; ++j) {
         if (a[j] % a[i] == 0) {
            a[j] = 0;
         }
      }
   }

   int amax = v.back();
   std::vector<int> vv(amax + 1, 1);

   // 或者可以通过 knapsack dp 找出能够组合出来的数字。
   for (auto av : v) {
      if (vv[av] == 1) {
         vv[av] = -1;
      }
      for (int i = 1; i <= amax - av; ++i) {
         if (vv[i] == -1 || vv[i] == 0) {
            vv[i + av] = 0;
         }
      }
   }

   int ans = 0;
   for (auto av : v) {
      if (vv[av] != 0) {
         ans++;
      }
   }


   printf("%d\n", ans);
   return 0;
}
