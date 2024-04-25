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

using LL = long long;

int X = 137;

int M0 = 1e9 + 7;
int M1 = 1e9 + 9;


constexpr int MAXL = 2000000;

char p[MAXL + 10];
char t[MAXL + 10];

int HashStr(char *s, int count) {
   int ret = 0;
   for (int i = 0; i < count; ++i) {
      ret = ((LL)ret * X + s[i]) % M0;
   }
   return ret;
}

int XPow(int power) {
   int ret = 1;
   for (int i = 0; i < power; i++) {
      ret = ((LL)ret * X) % M0;
   }
   return ret;
}

int StrDiff(char *s0, char *s1, int n) {
   int ret = 0;
   for (int i = 0; i < n; ++i) {
      ret += (s0[i] != s1[i]);
   }
   return ret;
}


int Solve(int k)
{
   int ret = 0;

   int pl = strlen(p);
   int tl = strlen(t);

   if (tl < pl)   return 0;
   if (pl <= k)   return pl - tl + 1;


   // 这里用了分割成 k 个部分的技巧；
   // 参考答案是：因为 k 有限制，最大为 10；所以利用这一特点，在 hash 比较之后，通过二分法找到到底是哪里不一样；（代替线性时间比较字符串）
   //           不过在二分法的过程中，如何快速计算 t 的子串的 hash 值，需要额外考虑。


   // split to 2*k parts.
   int segCount = min(pl, 2 * k);
   int segLen = pl / segCount;
   std::vector<int> pHash(segCount);
   for (int i = 0; i < segCount; ++i) {
      pHash[i] = HashStr(p + i * segLen, segLen);
   }
   int tailBegin = segCount * segLen;
   int tailCount = pl - tailBegin;

   std::vector<int> tHash(segCount);
   for (int i = 0; i < segCount; ++i) {
      tHash[i] = HashStr(t + i * segLen, segLen);
   }
   int tp = 0;
   int xpow = XPow(segLen - 1);
   while (tp + pl <= tl) {
      if (tp > 0) {
         for (int i = 0; i < segCount; ++i) {
            int outI = tp - 1 + i * segLen;
            int inI = outI + segLen;
            tHash[i] = (tHash[i] - (LL)t[outI] * xpow) % M0;
            tHash[i] = (((LL)tHash[i] + M0) * X + t[inI]) % M0;
         }
      }

      // Hash value cmp.
      int diffChs = 0;
      for (int i = 0; i < segCount; ++i) {
         if (pHash[i] != tHash[i]) {
            diffChs++;
         }
      }
      for (int i = 0; i < tailCount; ++i) {
         if (p[tailBegin + i] != t[tp + tailBegin + i]) {
            diffChs++;
         }
      }

      // This is a candidate.
      if (diffChs <= k) {
         for (int i = 0; i < segCount; ++i) {
            if (pHash[i] != tHash[i]) {
               diffChs += (StrDiff(p + i * segLen, t + tp + i * segLen, segLen) - 1);
            }
            if (diffChs > k) {
               break;
            }
         }
      }
      if (diffChs <= k) {
         ret += 1;
      }

      tp++;
   }

   return ret;
}


int main() {
   int k;
   scanf("%d", &k);
   scanf("%s%s", p, t);

   int ans = Solve(k);
   // 计算答案
   printf("%d\n", ans);
   return 0;
}
