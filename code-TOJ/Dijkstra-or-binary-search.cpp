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
const int N = 100000;
const int M = 200000;
const int MAXVALUE = 100001;

vector<vector<int> > edges;     // m 条边，使用邻接表存储
vector<int> vw;                  // n 个点的权值


vector<int> vMinPathMaxW;
vector<bool> vDiscovered;

// n: 同题目
// s: 同题目
// t: 同题目
// 返回值： s 到 t 的所有路径的最大值的最小值
int getAnswer(int n, int s, int t)
{
   /* 请在这里设计你的算法 */
   vMinPathMaxW.resize(n, MAXVALUE);
   vDiscovered.resize(n, false);
   //vParent.resize(n, -1);

   priority_queue<pair<int,int>, vector<pair<int, int>>, greater<pair<int, int>>> q; // weight, v
   q.push({vw[s], s});
   vDiscovered[s] = true;

   while (!q.empty()) {
      auto u = q.top(); q.pop();
      auto &vEdges = edges[u.second];
      for (auto v : vEdges) {
         if (!vDiscovered[v]) {
            auto w = max(u.first, vw[v]);
            if (v == t) {
               return w;
            }
            q.push({ w, v });
            vDiscovered[v] = true;
         }
      }
   }

   return -1;
}

/* ==================== 代码实现结束 ==================*/

int main()
{
   int n, m;
   scanf("%d%d", &n, &m);
   for (int i = 0; i < n; ++i) {
      int vi;
      scanf("%d", &vi);
      vw.push_back(vi);
   }
   edges.resize(n + 1);
   for (int i = 0; i < m; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      --u; --v;
      edges[u].push_back(v);
      edges[v].push_back(u);
   }
   int s, t;
   scanf("%d%d", &s, &t);
   --s; --t;
   printf("%d\n", getAnswer(n, s, t));
   return 0;
}
