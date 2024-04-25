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


constexpr int MAXN = 300005;

using namespace std;

unsigned int x[MAXN + 10];

// 或者可以用 trie 。把 二级制表示 看作字符串。
unsigned int Search(int n, unsigned int y)
{
   unsigned int pf = 0;
   int l = 0, r = n;
   for (int i = 0; i < 32; ++i) {
      unsigned int pfbit = (0x80000000 >> i);
      auto mid = lower_bound(x + l, x + r, pf | pfbit);
      if (mid == x + l) {
         pf |= pfbit;
      } else if (mid == x + r) {
         pf = pf;
      } else if (y & pfbit) {
         // select lower part
         pf = pf;
         r = mid - x;
      } else {
         // select higher part.
         pf |= pfbit;
         l = mid - x;
      }
   }

   return x[l] ^ y;
}

int main() {
   // n, q 含义同题目
   int n, q;
   scanf("%d%d", &n, &q);
   // x 为题目所给 n 个非负整数的数组
   for (int i = 0; i < n; i++) scanf("%u", x + i);

   sort(x, x + n);

   while (q--) {
      unsigned int y;
      scanf("%u", &y);
      // 对于当前给出的 y，计算查询，将结果存放于 ans
      unsigned int ans = Search(n, y);
      printf("%u\n", ans);
   }
   return 0;
}
