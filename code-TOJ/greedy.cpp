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

constexpr int N = 50'000;

bool isMine[N * 2 + 5];

int Solve(int n)
{
   std::vector<int> a;
   std::vector<int> b;
   for (int i = n * 2; i >= 1; --i) {
      if (isMine[i])
         a.push_back(i);
      else
         b.push_back(i);
   }

   int ret = 0;
   int ia = 0, ib = 0;
   while (ia < n && ib < n) {
      if (a[ia] < b[ib]) {
         ia++; ib++; ret++;
      } else {
         ia++;
      }
   }

   return ret;
}


int main() {
   int n, m;
   scanf("%d", &n);
   for (int i = 1; i <= n; ++i) {
      scanf("%d", &m);
      isMine[m] = true;
   }
   int ans = Solve(n);
   // 计算答案至 ans
   printf("%d\n", ans);
   return 0;
}
