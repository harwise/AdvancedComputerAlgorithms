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

const int N = 10005;

// 为了减少复制开销，我们直接读入信息到全局变量中，并统计了每个点的入度到数组in中
// n, m：点数和边数
// in：in[i]表示点i的入度
// e：e[i][j]表示点i的第j条边指向的点
int n, m, in[N];
vector<int> e[N];

/* 请在这里定义你需要的全局变量 */

// 判断所给有向无环图是否存在唯一的合法数列
// 返回值：若存在返回1；否则返回0。
bool getAnswer() {
   /* 请在这里设计你的算法 */

   int x = 0;
   for (int i = 1; i <= n; ++i) {
      if (in[i] == 0) {
         if (x != 0) {
            return 0;
         }
         x = i;
      }
   }

   int nodeRemoved = 0;
   while (nodeRemoved < n - 1) {
      int t = 0;
      for (int y : e[x]) {
         if (--in[y] == 0) {
            if (t != 0) {
               return 0;
            }
            t = y;
         }
         x = t;
      }

      nodeRemoved++;
   }


   return 1;
}

// ================= 代码实现结束 =================

int main() {
   int T;
   for (scanf("%d", &T); T--; ) {
      scanf("%d%d", &n, &m);
      for (int i = 1; i <= n; ++i) {
         in[i] = 0;
         e[i].clear();
      }
      for (int i = 0; i < m; ++i) {
         int x, y;
         scanf("%d%d", &x, &y);
         e[x].push_back(y);
         ++in[y];
      }
      printf("%d\n", getAnswer());
   }
   return 0;
}
