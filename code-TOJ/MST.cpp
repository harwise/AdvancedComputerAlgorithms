#include <stdio.h>
#include <stack>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <queue>

using namespace std;


// ================= 代码实现开始 =================

/* 请在这里定义你需要的全局变量 */

#define N 200005

int gParent[N];
int gRank[N];

int GetRoot(int x) {
   if (gParent[x] == x) {
      return x;
   }
   gParent[x] = GetRoot(gParent[x]);
   return gParent[x];
}

void Merge(int x1, int x2) {
   int r1 = GetRoot(x1);
   int r2 = GetRoot(x2);
   if (r1 == r2) {
      return;
   }
   if (gRank[r1] < gRank[r2]) {
      swap(r1, r2);
   }
   gParent[r2] = r1;
   if (gRank[r1] == gRank[r2]) {
      gRank[r1] += 1;
   }
}

/* 请在这里定义你需要的全局变量 */

// 给定一个n个点m条边的无向图，第i条边边权为i，求所有需要升级的边
// n：如题意
// m：如题意
// U：大小为m的数组，表示m条边的其中一个端点
// V：大小为m的数组，表示m条边的另一个端点
// 返回值：所有需要升级的边，从小到大排列；第一小问的答案自然即为返回值的size，所以你不必考虑如何返回size
vector<int> getAnswer(int n, int m, vector<int> U, vector<int> V) {
   /* 请在这里设计你的算法 */

   vector<int> ret;

   // init
   for (int i = 0; i < n + 1; ++i) {
      gParent[i] = i;
   }

   for (int i = m - 1; i >= 0; --i) {
      if (GetRoot(U[i]) == GetRoot(V[i])) {
         continue;
      }
      Merge(U[i], V[i]);
      ret.push_back(i + 1);
   }

   return ret;
}

// ================= 代码实现结束 =================

int main() {
   int n, m;
   scanf("%d%d", &n, &m);
   vector<int> U, V;
   for (int i = 0; i < m; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      U.push_back(u);
      V.push_back(v);
   }
   vector<int> ans = getAnswer(n, m, U, V);
   printf("%d\n", int(ans.size()));
   for (int i = 0; i < int(ans.size()); ++i)
      printf("%d\n", ans[ans.size() - 1 - i]);
   return 0;
}
