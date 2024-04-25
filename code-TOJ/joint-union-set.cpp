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

#define N 300005

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
   if (gRank[r1] <= gRank[r2]) {
      gParent[r1] = r2;
      gRank[r2] = max(gRank[r1] + 1, gRank[r2]);
   } else {
      gParent[r2] = r1;
      gRank[r1] = max(gRank[r1], gRank[r2] + 1);
   }
}

// 给定n个变量以及m个约束，判定是否能找出一种赋值方案满足这m个约束条件
// n：如题意
// m：如题意
// A：大小为m的数组，表示m条约束中的a
// B：大小为m的数组，表示m条约束中的b
// E：大小为m的数组，表示m条约束中的e
// 返回值：若能找出一种方案，返回"Yes"；否则返回"No"（不包括引号）。
string getAnswer(int n, vector<pair<int, int>> &&Eq, vector<pair<int, int>> &&NotEq) {
   /* 请在这里设计你的算法 */

   for (int i = 0; i < n + 1; ++i) {
      gParent[i] = i;
      gRank[i] = 0;
   }
   for (int i = 0; i < Eq.size(); ++i) {
      Merge(Eq[i].first, Eq[i].second);
   }
   for (int i = 0; i < NotEq.size(); ++i) {
      if (GetRoot(NotEq[i].first) == GetRoot(NotEq[i].second)) {
         return "No";
      }
   }
   return "Yes";
}

// ================= 代码实现结束 =================

int main() {
   int T;
   for (scanf("%d", &T); T--; ) {
      int n, m;
      scanf("%d%d", &n, &m);
      vector<std::pair<int,int>> Eq, NotEq;
      for (int i = 0; i < m; ++i) {
         int a, b, e;
         scanf("%d%d%d", &a, &b, &e);
         if (e == 0) {
            NotEq.push_back({ a, b });
         } else {
            Eq.push_back({ a, b });
         }
      }
      printf("%s\n", getAnswer(n, move(Eq), move(NotEq)).c_str());
   }
   return 0;
}
