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

#define MAXN 2000
#define OFFSET(x) (x + 1000)

using namespace std;

struct Point {
   int x, y;
   Point(int x = 0, int y = 0) : x(x), y(y) {}
};

Point AtoB(const Point &a, const Point &b) {
   return { b.x - a.x, b.y - a.y };
}

int GCD(int a, int b) {
   static int cache[MAXN / 2 + 5][MAXN / 2 + 5];
   if (cache[a][b] != 0) {
      return cache[a][b];
   }

   if (a % b == 0)
      return cache[a][b] = b;
   return cache[a][b] = GCD(b, a % b);
}

Point Simplify(const Point &p) {
   int gcd = GCD(p.x > 0 ? p.x : -p.x,
      p.y > 0 ? p.y : -p.y);
   return { p.x / gcd, p.y / gcd };
}

vector<Point> p;

int lineCount[MAXN + 5][MAXN + 5];

long long solve() {
   long long ret = 0;
   for (int i = 0; i < p.size(); ++i) {
      //memset(lineCount, 0x00, sizeof(lineCount));
      vector<pair<int, int>> dirty;
      for (int j = 0; j < p.size(); ++j) {
         if (i == j) continue;
         Point line = AtoB(p[i], p[j]);
         if (line.x == 0 && line.y == 0) continue;
         if (line.x == 0) {
            lineCount[OFFSET(0)][OFFSET(1)]++;
            ret += lineCount[OFFSET(1)][OFFSET(0)];
         } else if (line.y == 0) {
            lineCount[OFFSET(1)][OFFSET(0)]++;
            ret += lineCount[OFFSET(0)][OFFSET(1)];
         } else {
            line = Simplify(line);
            lineCount[OFFSET(line.x)][OFFSET(line.y)]++;
            ret += lineCount[OFFSET(-line.y)][OFFSET(line.x)];
            ret += lineCount[OFFSET(line.y)][OFFSET(-line.x)];
            dirty.push_back({ OFFSET(line.x), OFFSET (line.y)});
         }
      }

      lineCount[OFFSET(1)][OFFSET(0)] = 0;
      lineCount[OFFSET(0)][OFFSET(1)] = 0;
      for (const auto &c : dirty) {
         lineCount[c.first][c.second] = 0;
      }
   }
   return ret;
}

int main() {
   int n;
   scanf("%d", &n);
   for (int i = 0; i < n; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      p.emplace_back(x, y);
   }
   long long ans = solve();
   printf("%lld\n", ans);
   return 0;
}
