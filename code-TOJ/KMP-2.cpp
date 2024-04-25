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


constexpr int MAXL = 1000000;
constexpr int MOD = 1e9 + 7;

char s[MAXL + 10];

int N[MAXL + 10];
int C[MAXL + 10];

int Solve(int len)
{
   s[len++] = '$';

   int i = -1;
   int j = 0;
   N[0] = -1;
   C[0] = -1;    // how many substrings(prefix==suffix) it contains.
   while (j < len - 1) {
      if (i < 0 || s[i] == s[j]) {
         N[++j] = ++i;
         C[j] = C[i] + 1;
      } else {
         i = N[i];
      }
   }

   long long ret = 1;
   i = -1, j = 0;
   while (j < len - 1) {
      if (i < 0 || (i <= (j-1)/2 && s[i] == s[j])) {
         ++j; ++i;
         ret = ((C[i] + 1 + 1) * ret) % MOD;     // C[i] + 1 : C[i] is for all substrings; 1 is for itself.
      } else {
         i = N[i];
      }
   }

   return ret;
}


int main() {
   scanf("%s", s);
   int len = strlen(s);
   int ans = Solve(len);
   // 计算答案至 ans
   printf("%d\n", ans);
   return 0;
}
