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


// ================= 代码实现开始 =================

typedef unsigned int u32;

// 以下代码不需要解释，你只需要知道这是用于生成数据的就行了

u32 nextInt(u32 x) {
   x ^= x << 13;
   x ^= x >> 17;
   x ^= x << 5;
   return x;
}

void initData(u32 *a, int n, int k, u32 seed) {
   for (int i = 0; i < n; ++i) {
      seed = nextInt(seed);
      a[i] = seed >> (32 - k);
   }
}

// 以上代码不需要解释，你只需要知道这是用于生成数据的就行了

/* 请在这里定义你需要的全局变量 */

const int N = 1 << 26;  // 67108864;   最多有 N 个数。

u32 a[N + 1];
u32 l[N + 1], r[N + 1];

// 这是求解答案的函数，你需要对全局变量中的 a 数组求解 maxGap 问题
// n, k：意义与题目描述相符
// 返回值：即为答案（maxGap）
u32 maxGap(int n, int k) {
   /* 请在这里设计你的算法 */

   memset(l, -1, sizeof(l));
   memset(r, -1, sizeof(r));

   const int kk = max(k - 26, 0);      // 值的范围 [0, 2^k] k = 16 or 32.
   for (int i = 0; i < n; ++i) {
      u32 bl = a[i] >> kk;             // a[i]应该在哪个桶里。
      if (l[bl] == -1) {
         l[bl] = r[bl] = a[i];
      } else if (a[i] < l[bl]) {
         l[bl] = a[i];
      } else if (a[i] > r[bl]) {
         r[bl] = a[i];
      }
   }

   u32 last = a[0];
   u32 ans = 0;

   for (int i = 0; i < N; ++i) {
      if (l[i] != -1) {
         if (last > l[i])
            last = l[i];
         if (l[i] - last > ans) {
            ans = l[i] - last;
         }
         last = r[i];
      }
   }

   return ans;
}

// ================= 代码实现结束 =================

int main() {
   int n, k;
   u32 seed;

   scanf("%d%d%u", &n, &k, &seed);
   initData(a, n, k, seed);

   u32 ans = maxGap(n, k);

   printf("%u\n", ans);
   return 0;
}
