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


#define MAXN 5000

using namespace std;

char a[MAXN + 10], b[MAXN + 10];
int na, nb;

int solve() {
   vector<int> dp(nb + 5);
   for (int i = 0; i <= nb; ++i) {
      dp[i] = i;
   }

   vector<int> dp1(nb + 5);
   for (int i = 1; i <= na; ++i) {
      dp1[0] = dp[0] + 1;
      for (int j = 1; j <= nb; ++j) {
         dp1[j] = dp1[j - 1] + 1;
         dp1[j] = max(dp1[j], dp[j] + 1);
         if (a[i] == b[j]) {
            dp1[j] = max(dp1[j], dp[j - 1] + 4);
         } else {
            dp1[j] = max(dp1[j], dp[j - 1] + 2);
         }
      }
      swap(dp, dp1);
   }

   return dp[nb];
}

int main() {
   scanf("%d%s", &na, a + 1);
   scanf("%d%s", &nb, b + 1);
   printf("%d\n", solve());
   return 0;
}
