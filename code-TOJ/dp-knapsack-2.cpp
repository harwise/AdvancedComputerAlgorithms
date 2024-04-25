#include <stdio.h>
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

/* 请在这里定义你需要的全局变量 */

const int N = 5005;
const int V = 5005;

int d[N][V], f[N][V];


// n个物品，每个物品有体积价值，求若扔掉一个物品后装进给定容量的背包的最大价值
// n：如题
// w：长度为n+1的数组，w[i]表示第i个物品的价值（下标从1开始，下标0是一个数字-1，下面同理）
// v：长度为n+1的数组，v[i]表示第i个物品的体积
// q：如题
// qV：长度为q+1的数组，qV[i]表示第i次询问所给出的背包体积
// qx：长度为q+1的数组，qx[i]表示第i次询问所给出的物品编号
// 返回值：返回一个长度为q的数组，依次代表相应询问的答案
vector<int> getAnswer(int n, vector<int> w, vector<int> v, int q, vector<int> qV, vector<int> qx) {
   /* 请在这里设计你的算法 */

   // left
   for (int i = 1; i <= n; ++i) {
      for (int vv = 0; vv < v[i]; ++vv) {
         d[i][vv] = d[i - 1][vv];
      }
      for (int vv = v[i]; vv <= 5000; ++vv) {
         d[i][vv] = max(d[i - 1][vv], d[i - 1][vv - v[i]] + w[i]);
      }
   }

   // right
   for (int i = n; i >= 1; --i) {
      for (int vv = 0; vv < v[i]; ++vv) {
         f[i][vv] = f[i + 1][vv];
      }
      for (int vv = v[i]; vv <= 5000; ++vv) {
         f[i][vv] = max(f[i + 1][vv], f[i + 1][vv - v[i]] + w[i]);
      }
   }

   vector<int> ans;
   for (int k = 1; k <= q; k++) {
      int x = qx[k], xv = qV[k];
      int mx = 0;

      for (int vv = 0; vv <= xv; ++vv) {
         mx = max(mx, d[x - 1][vv] + f[x + 1][xv - vv]);
      }
      ans.push_back(mx);
   }

   return ans;
}

// ================= 代码实现结束 =================

int main() {
   int n, q;
   vector<int> v, w, qv, qx;
   v.push_back(-1);
   w.push_back(-1);
   qv.push_back(-1);
   qx.push_back(-1);
   scanf("%d", &n);
   for (int i = 0; i < n; ++i) {
      int a, b;
      scanf("%d%d", &a, &b);
      v.push_back(a);
      w.push_back(b);
   }
   scanf("%d", &q);
   for (int i = 0; i < q; ++i) {
      int a, b;
      scanf("%d%d", &a, &b);
      qv.push_back(a);
      qx.push_back(b);
   }
   vector<int> ans = getAnswer(n, w, v, q, qv, qx);
   for (int i = 0; i < q; ++i)
      printf("%d\n", ans[i]);
   return 0;
}

