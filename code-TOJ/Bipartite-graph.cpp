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

constexpr int N = 505 * 2, M = N * N;

struct E {
   int to;        // the target endpoint
   int next;      // next edge
} e[M];

int cnt;          // count of edges
int ihead[N];     // 点i 的 edges in list.
int mc[N];
bool vis[N];

void add(int x, int y) {
   ++cnt;
   e[cnt].next = ihead[x];
   e[cnt].to = y;
   ihead[x] = cnt;
}

bool dfs(int x) {
   for (int i = ihead[x]; i; i = e[i].next) {
      int y = e[i].to;
      if (!vis[y]) {
         vis[y] = true;
         if (mc[y] == 0 || dfs(mc[y])) {
            mc[x] = y;
            mc[y] = x;
            return true;
         }
      }
   }
   return false;
}

// 求解棋盘上最多能放多少个“车”
// n：棋盘的大小为n×n的
// board：所给棋盘，对于某个位置上的数：若值为1表示可以放“车”；若值为0表示不能放“车”
// 返回值：能放“车”的最大个数
int getAnswer(int n, vector<vector<int>> board) {
   /* 请在这里设计你的算法 */

   cnt = 0;
   for (int i = 1; i <= n * 2; ++i) {
      ihead[i] = 0;
      mc[i] = 0;
   }

   for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
         if (board[i - 1][j - 1] == 1) {
            add(i, n + j);
            add(n + j, i);
         }
      }
   }

   int ans = 0;
   for (int i = 1; i <= n; ++i) {
      if (mc[i] == 0) {
         fill(vis, vis + (n * 2 + 1), 0);
         if (dfs(i))
            ++ans;
      }
   }

   return ans;
}

// ================= 代码实现结束 =================

int main() {
   int n;
   scanf("%d", &n);
   vector<vector<int>> e;
   for (int i = 0; i < n; ++i) {
      vector<int> t;
      for (int j = 0; j < n; ++j) {
         int x;
         scanf("%d", &x);
         t.push_back(x);
      }
      e.push_back(t);
   }
   printf("%d\n", getAnswer(n, e));
   return 0;
}
