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
#include <cmath>
#include <algorithm>
#include <numeric>

using namespace std;

constexpr int MAXN = 100000;
constexpr int MAXM = 300000;

struct Edge {
   int u, v, w;
} e[MAXM + 10];

std::vector<std::vector<int>> vEdges;
std::vector<int> vVisited;

bool Dfs(int v, int color)
{
   vVisited[v] = color;
   for (int u : vEdges[v]) {
      if (vVisited[u] == color) {
         return false;
      }
      if (vVisited[u] == 0) {
         if (Dfs(u, color * -1) == false)
            return false;
      }
   }
   return true;
}

bool IsBipartite(int n, int eEnd)
{
   vEdges = std::vector<std::vector<int>>(n + 1);
   for (int i = 0; i < eEnd; ++i) {
      vEdges[e[i].u].push_back(e[i].v);
      vEdges[e[i].v].push_back(e[i].u);
   }

   vVisited = std::vector<int>(n + 1);
   for (int i = 1; i <= n; ++i) {
      if (vVisited[i] == 0) {
         if (Dfs(i, 1) == false)
            return false;
      }
   }
   return true;
}

int Solve(int n, int m)
{
   std::sort(e, e + m, [](const Edge& lhs, const Edge& rhs) {
      return lhs.w > rhs.w;
      });

   int l = 0, r = m;
   while (l < r) {
      int c = (l + r) / 2;
      if (IsBipartite(n, c)) {
         l = c + 1;     // before l is OK.
      } else {
         r = c;         // r is not OK.
      }
   }

   r = r - 1;  // the last one which is OK.
   return r > 0 ? e[r].w : 0;
}


int main() {
   int n, m;
   scanf("%d%d", &n, &m);
   for (int i = 0; i < m; i++) {
      auto &e = ::e[i];
      scanf("%d%d%d", &e.u, &e.v, &e.w);
   }
   int ans = 0;
   //计算答案至 ans;

   ans = Solve(n, m);

   printf("%d\n", ans);

   return 0;
}
