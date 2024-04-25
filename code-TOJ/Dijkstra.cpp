#include <stdio.h>
#include <stack>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <queue>
#include <limits>

using namespace std;

// ================= 代码实现开始 =================

/* 请在这里定义你需要的全局变量 */
const int N = 100005;
using pii = std::pair<int, int>;    // weight; destination node

vector<pii> graph[N];
priority_queue<pii, vector<pii>, greater<pii>> pq;

bool flag[N];
int minDist[N];


// 这个函数用于计算答案（最短路）
// n：节点数目
// m：双向边数目
// U,V,W：分别存放各边的两端点、边权
// s,t：分别表示起点、重点
// 返回值：答案（即从 s 到 t 的最短路径长度）
int shortestPath(int n, int m, vector<int> U, vector<int> V, vector<int> W, int s, int t) {
   /* 请在这里设计你的算法 */

   std::fill(minDist, minDist + N, std::numeric_limits<int>::max());

   for (int i = 0; i < m; ++i) {
      graph[U[i]].push_back({ W[i], V[i] });
      graph[V[i]].push_back({ W[i], U[i] });
   }

   minDist[s] = 0;
   pq.push({ 0, s });

   while (!pq.empty()) {
      int u = pq.top().second;   pq.pop();
      if (u == t) {
         return minDist[t];
      }
      if (!flag[u]) {
         flag[u] = true;
         for (auto &e : graph[u]) {
            int v = e.second;
            int w = e.first;
            if (minDist[u] + w >= minDist[v])
               continue;
            minDist[v] = minDist[u] + w;
            pq.push({ minDist[v], v });
         }
      }
   }

   return minDist[t];
}

// ================= 代码实现结束 =================

int main() {
   int n, m, s, t;
   scanf("%d%d%d%d", &n, &m, &s, &t);
   vector<int> U, V, W;
   U.clear();
   V.clear();
   W.clear();
   for (int i = 0; i < m; ++i) {
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      U.push_back(u);
      V.push_back(v);
      W.push_back(w);
   }

   printf("%d\n", shortestPath(n, m, U, V, W, s, t));
   return 0;
}
