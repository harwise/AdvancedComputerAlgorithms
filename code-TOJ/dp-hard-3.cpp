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

using namespace std;

constexpr int N = 1000 + 5;

using vp = vector<pair<int, int>>;
vp bestScores[N];
int bestScoresCur[N];

// 实际上可以用 DP 做，状态 dp[i][j] 表示：上一个位置是 i ，当前位置是 j 的时候，拿到的最大分数。根据 i，j 的值，可以得到当前能够跳跃的距离。

int Solve(const vp &points, bool reverse)
{
   int ret = 0;
   for (int i = 0; i < points.size(); ++i) {
      bestScores[i].push_back({ 0, points[i].second });
      for (int j = i - 1; j >= 0; j--) {
         int dist = (points[i].first - points[j].first) * (reverse ? -1 : 1);
         int &cur = bestScoresCur[j];
         while (cur < bestScores[j].size() &&
                bestScores[j][cur].first <= dist) {
            cur++;
         }
         cur -= 1;
         int score = bestScores[j][cur].second + points[i].second;
         if (score > bestScores[i].back().second) {
            bestScores[i].push_back({dist, score});
            ret = max(ret, score);
         }
      }
   }
   return ret;
}


int main() {
   int n;
   scanf("%d", &n);
   vp dvs(n);
   for (int i = 0; i < n; ++i) {
      scanf("%d %d", &dvs[i].first, &dvs[i].second);
   }
   std::sort(dvs.begin(), dvs.end());
   int ans1 = Solve(dvs, false);

   memset(bestScores, 0x00, sizeof(bestScores));
   memset(bestScoresCur, 0x00, sizeof(bestScoresCur));
   for (int i = 0; i < n / 2; ++i) {
      swap(dvs[i], dvs[n - 1 - i]);
   }
   int ans2 = Solve(dvs, true);

   // 计算答案至 ans
   printf("%d\n", max(ans1, ans2));
   return 0;
}
