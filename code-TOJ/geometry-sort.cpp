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
   return {b.x - a.x, b.y - a.y};
}

int AcrossB(const Point &a, const Point &b) {
   return a.x *b.y - b.x * a.y;
}

int AdotB(const Point &a, const Point &b) {
   return a.x * b.x + a.y * b.y;
}

bool AlessB(const Point &a, const Point &b) {
   return AcrossB(a, b) > 0;
}

vector<Point> p;

long long solve() {
   long long ret = 0;
   int n = p.size();
   for (int i = 0; i < n; ++i) {
      Point center = p[i];
      //swap(p[i], p[n - 1]);
      std::vector<Point> lines;
      for (int j = 0; j < n; ++j) {
         Point line = AtoB(center, p[j]);
         if (line.x == 0 && line.y == 0) {
            continue;
         }
         if (line.x == 0) {
            lines.push_back({0, 1});
         } else if (line.x < 0) {
            lines.push_back({ -line.x, -line.y });
         } else {
            lines.push_back(line);
         }
      }

      sort(lines.begin(), lines.end(), AlessB);

      int jj = 1;
      int count = 0;
      for (int ii = 0; ii < lines.size(); ++ii) {
         if (ii > 0 && AcrossB(lines[ii], lines[ii - 1]) == 0) {
            ret += count;
            continue;
         }
         count = 0;
         while (jj < lines.size() && AdotB(lines[ii], lines[jj]) > 0) {
            jj++;
         }
         while (jj < lines.size() && AdotB(lines[ii], lines[jj]) == 0) {
            count++;
            jj++;
         }
         ret += count;
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
