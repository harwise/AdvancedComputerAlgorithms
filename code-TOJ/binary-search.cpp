#include <stdio.h>
#include <stack>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <queue>

using namespace std;

/*
40 17
8 8 6 7 9 4 6 3 1 10 9 7 9 7 1 2 1 5 6 10 9 4 3 6 1 10 10 7 8 2 3 5 9 8 3 9 2 10 1 4

8 8 
6 7 
9 4 
6 3 1 
10 
9 7 
9 7 1 
2 1 5 6 
10 
9 4 3 
6 1 10 
10 7 
8 2 3 
5 9 
8 3 
9 2 
10 1 4
*/


// ================= 代码实现开始 =================

/* 请在这里定义你需要的全局变量 */

bool check(long long v, int m, const vector<int> &a) {
   long long sum = 0;
   int cnt = 0;

   int i = 0;
   while (i < a.size()) {
      if (a[i] > v) {
         return false;
      }
      if (sum + a[i] <= v) {
         sum += a[i];
         i++;
      } else {
         sum = 0;
         cnt++;
         if (cnt > m) {
            return false;
         }
      }
   }
   if (sum != 0) {
      cnt++;
   }

   return cnt <= m;
}

// 将所给数组分成连续的m份，使得数字之和最大的那一份的数字之和最小
// n：数组大小
// m：题中的m
// a：所给数组，大小为n
// 返回值：最优方案中，数字之和最大的那一份的数字之和
long long getAnswer(int n, int m, vector<int> a) {
   /* 请在这里设计你的算法 */

   long long l = 1;
   long long r = 1000000ll *300000;

   // Invariants:
   // dropped_left, [l, mid), mid, [mid + 1, h), h, dropped_right
   //
   // l:                its left is smaller / or out of range.
   // h:                a[h] is alwasy greater / or out of range.
   //
   // when l == h, this is the target point. Because:
   // It is the right-most one whose left neighour is smaller than X.
   // It is the left-most one that is greater than X.

   while (l < r) {
      auto mid = (l + r) / 2;
      if (check(mid, m, a)) {
         r = mid;
      } else {
         l = mid + 1;
      }
   }

   return r;
}

// ================= 代码实现结束 =================

int main() {
   int n, m;
   scanf("%d%d", &n, &m);
   vector<int> a;
   a.resize(n);
   for (int i = 0; i < n; ++i)
      scanf("%d", &a[i]);
   printf("%lld\n", getAnswer(n, m, a));
   return 0;
}
