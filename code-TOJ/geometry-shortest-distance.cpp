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

using LL = long long;

constexpr int MAXN = 500000;

struct Point { int x, y, c; };

Point p[MAXN + 10];


inline LL DistSq(const std::pair<int, int>& a, const std::pair<int, int>& b)
{
   return (LL)(a.first - b.first) * (a.first - b.first) + (LL)(a.second - b.second) * (a.second - b.second);
}

inline LL Square(int x)
{
   return (LL)x * x;
}

struct CompareY
{
   bool operator()(const std::pair<int, int> &lhs, const std::pair<int, int> &rhs) const
   {
      return lhs.second == rhs.second ? lhs.first < rhs.first: lhs.second < rhs.second;
   }
};


LL Solve(int n) {

   std::vector<std::pair<int,int>> set0;
   std::vector<std::pair<int,int>> set1;
   for (int i = 0; i < n; ++i) {
      if (p[i].c == 0) {
         set0.push_back({p[i].x, p[i].y});
      } else {
         set1.push_back({ p[i].x, p[i].y });
      }
   }

   //set0.erase(std::unique(set0.begin(), set0.end()), set0.end());
   //set1.erase(std::unique(set1.begin(), set1.end()), set1.end());

   std::sort(set0.begin(), set0.end());
   std::sort(set1.begin(), set1.end());

   if (set0.empty() || set1.empty())
      return 0;



   //LL minCC = std::numeric_limits<LL>::max();
   //for (auto p0 : set0)
   //   for (auto p1 : set1)
   //      minCC = min(minCC, DistSq(p0, p1));

   //printf("%lld\n", minCC);
   //


   if (set0[0].first > set1[0].first)
      std::swap(set0, set1);

   LL minDistSq = DistSq(set0[0], set1[0]);
   minDistSq = min(minDistSq, DistSq(set0[0], *set1.rbegin()));
   minDistSq = min(minDistSq, DistSq(*set0.rbegin(), set1[0]));
   minDistSq = min(minDistSq, DistSq(*set0.rbegin(), *set1.rbegin()));

   std::set<std::pair<int, int>, CompareY> ySorted;
   int x = set0[0].first;
   int l = 0, r = 0;
   while (r < set1.size()) {
      if (Square(set1[r].first - x) <= minDistSq) {
         ySorted.insert(set1[r]);
      } else {
         break;
      }
      r++;
   }

   for (auto &p0 : set0) {
      int x = p0.first;
      // update x range - shrink left.
      while (l < r) {
         if (set1[l].first < x && Square(set1[l].first - x) > minDistSq) {
            ySorted.erase(set1[l]);
         } else {
            break;
         }
         l++;
      }
      // update x range - expand right.
      while (r < set1.size()) {
         if (Square(set1[r].first - x) <= minDistSq) {
            ySorted.insert(set1[r]);
         } else if (set1[r].first > x) {
            break;
         }
         r++;
      }

      int y = p0.second;
      int minDist = (sqrt(minDistSq) + 1);
      auto lo = ySorted.lower_bound({ std::numeric_limits<int>::min(), y - minDist});
      auto hi = ySorted.upper_bound({ std::numeric_limits<int>::max(), y + minDist });
      int i = 0;
      for (; lo != hi; lo++, i++) {
         minDistSq = min(minDistSq, DistSq(p0, *lo));
      }
      if (minDistSq == 0)
         return 0;
   }

   //if (minCC != minDistSq)
   //   scanf("%d", &n);

   return minDistSq;
}



int main() {
   int n;
   scanf("%d", &n);
   for (int i = 0; i < n; i++) scanf("%d%d%d", &p[i].x, &p[i].y, &p[i].c);
   LL ans = Solve(n);
   // 计算答案至 ans
   printf("%lld\n", ans);

   //while (1) {
   //   n = 9;
   //   for (int i = 0; i < n; ++i) {
   //      p[i].x = rand() % 10;
   //      p[i].y = rand() % 10;
   //      p[i].c = rand() % 2;
   //      printf("%d %d %d\n", p[i].x, p[i].y, p[i].c);
   //   }
   //   LL ans = Solve(n);
   //   // 计算答案至 ans
   //   printf("%lld\n", ans);
   //}

   return 0;
}
