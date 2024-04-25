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

const int N = 1005;
const int64_t mo1 = 1e9 + 7;
const int64_t mo2 = 1e9 + 9;
const int64_t pw = 233;           // base

int64_t h1[2][N][N]; // a ==横向hash==> h1[0] ==纵向hash==> h1[1] with mo1
int64_t h2[2][N][N]; // a ==横向hash==> h1[0] ==纵向hash==> h1[1] with mo2

int64_t b1[N][N]; // b ==横向hash==> bb ==纵向hash==> 结果是标量 with mo1
int64_t b2[N][N]; // b ==横向hash==> bb ==纵向hash==> 结果是标量 with mo2

/* 请在这里定义你需要的全局变量 */

// 为了减少复制开销，我们直接读入信息到全局变量中
// a, b：题目所述数组，a的大小为(n+1)*(m+1)，b的大小为(p+1)*(q+1)，下标均从1开始有意义（下标0无意义，你可以直接无视）
// n, m, p, q：题中所述
int a[N][N], b[N][N], n, m, p, q;

// 求出a中有哪些位置出现了b
// 返回值：一个pair<int, int>的数组，包含所有出现的位置
vector<pair<int, int>> getAnswer() {
   /* 请在这里设计你的算法 */

   // p1 = (-pw ^ q)     取模，按整数求
   int64_t p1 = 1, p2 = 1;

   for (int i = 1; i <= q; ++i) {
      p1 = p1 * pw % mo1;
      p2 = p2 * pw % mo2;
   }
   p1 = (mo1 - p1) % mo1;
   p2 = (mo2 - p2) % mo2;

   // a => 横向 hash 值
   for (int i = 1; i <= n; ++i) {
      int64_t t1 = 0, t2 = 0;
      for (int j = 1; j <= m; ++j) {
         if (j < q) {
            // a[0]*pw^(j-1) + a[1]*pw^(j-2) + ...
            t1 = (t1 * pw + a[i][j]) % mo1;
            t2 = (t2 * pw + a[i][j]) % mo2;
         } else {
            t1 = h1[0][i][j] = (t1 * pw + a[i][j] + p1 * a[i][j - q]) % mo1;
            t2 = h2[0][i][j] = (t2 * pw + a[i][j] + p2 * a[i][j - q]) % mo2;
         }
      }
   }

   p1 = 1, p2 = 1;
   for (int i = 1; i <= p; ++i) {
      p1 = p1 * pw % mo1;
      p2 = p2 * pw % mo2;
   }
   p1 = (mo1 - p1) % mo1;
   p2 = (mo2 - p2) % mo2;

   // a => 横向 hash 值 => 纵向 hash 值
   for (int j = 1; j <= m; ++j) {
      int64_t t1 = 0, t2 = 0;
      for (int i = 1; i <= n; ++i) {
         if (i < p) {
            // a[0]*pw^(j-1) + a[1]*pw^(j-2) + ...
            t1 = (t1 * pw + h1[0][i][j]) % mo1;
            t2 = (t2 * pw + h2[0][i][j]) % mo2;
         } else {
            t1 = h1[1][i][j] = (t1 * pw + h1[0][i][j] + p1 * h1[0][i - p][j]) % mo1;
            t2 = h2[1][i][j] = (t2 * pw + h2[0][i][j] + p2 * h2[0][i - p][j]) % mo2;
         }
      }
   }

   // b => 横向 hash 值
   for (int i = 1; i <= p; ++i) {
      for (int j = 1; j <= q; ++j) {
         b1[i][j] = (b1[i][j - 1] * pw + b[i][j]) % mo1;
         b2[i][j] = (b2[i][j - 1] * pw + b[i][j]) % mo2;
      }
   }

   // b => 横向 hash 值 => 最终 hash 值
   p1 = p2 = 0;
   for (int i = 1; i <= p; ++i) {
      p1 = (p1 * pw + b1[i][q]) % mo1;
      p2 = (p2 * pw + b2[i][q]) % mo2;
   }

   vector<pair<int, int>> ans;
   for (int i = p; i <= n; ++i)
      for (int j = q; j <= m; ++j)
         if (h1[1][i][j] == p1 && h2[1][i][j] == p2)
            ans.push_back({i - p + 1, j - q + 1});
   return ans;
}

// ================= 代码实现结束 =================

int main() {
   scanf("%d%d%d%d", &n, &m, &p, &q);
   for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
         scanf("%d", &a[i][j]);
   for (int i = 1; i <= p; ++i)
      for (int j = 1; j <= q; ++j)
         scanf("%d", &b[i][j]);
   vector<pair<int, int>> ans = getAnswer();
   for (int i = 0; i < int(ans.size()); ++i)
      printf("%d %d\n", ans[i].first, ans[i].second);
   return 0;
}
