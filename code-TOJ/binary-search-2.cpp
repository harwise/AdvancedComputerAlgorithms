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
constexpr int MAXN = 500000;

struct Edge {
   int u, v, w;
};

vector<Edge> to[MAXN + 10];
int n, k;


bool pfs(int w)
{
   /* 请在这里设计你的算法 */
   vector<int> vDiscovered(n + 1, false);

   priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q; // weight, v
   q.push({ 0, 1 });
   vDiscovered[1] = true;

   while (!q.empty()) {
      auto u = q.top(); q.pop();
      if (u.first > k) {
         return false;
      }
      auto &vEdges = to[u.second];
      for (auto v : vEdges) {
         if (!vDiscovered[v.v]) {
            int vk = u.first;
            if (v.w > w) {
               vk++;
            }
            if (vk <= k) {
               q.push({ vk, v.v });
               vDiscovered[v.v] = true;
               if (v.v == n) {
                  return true;
               }
            }
         }
      }
   }

   return false;
}


// n: 同题目
// s: 同题目
// t: 同题目
// 返回值： s 到 t 的所有路径的最大值的最小值
int getAnswer(int _n, int _k)
{
   n = _n;
   k = _k;

   // false, false, true, ....
   int minW = 0;
   int maxW = 23333;    // definitely true
   while (minW < maxW) {
      int w = (minW + maxW) / 2;
      if (!pfs(w)) {
         minW = w + 1;
      } else {
         maxW = w;
      }
   }

   return maxW;
}

/* ==================== 代码实现结束 ==================*/

int main() {
   int m;
   scanf("%d%d%d", &n, &m, &k);
   while (m--) {
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      to[u].push_back(Edge{ u, v, w });
      to[v].push_back(Edge{ v, u, w });
   }
   int ans = getAnswer(n, k);
   // 计算答案
   printf("%d\n", ans);
   return 0;
}
