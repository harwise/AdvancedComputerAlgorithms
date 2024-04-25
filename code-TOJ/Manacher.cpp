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

const int N = 500005;

/* 请在这里定义你需要的全局变量 */
char s[N * 2];
int len[N * 2];

// 计算str中有多少个回文子串
// 返回值：子串的数目
long long getAnswer(string str) {
   /* 请在这里设计你的算法 */
   int n = str.size();

   for (int i = n; i > 0; --i) {
      s[i << 1] = str[i - 1];
      s[i << 1 | 1] = 0;
   }

   // 0 1 [2] 3 4 5 [2*3] 7 [2*3 + 2]
   // 1 #  a  # b #   c   #     2

   // 0 1 [2] 3 [2*2] 5 [2*2 + 2]
   // 1 #  a  #   b   #     2

   n = n << 1 | 1;
   s[1] = 0;
   s[0] = 1, s[n + 1] = 2;

   // manacher
   int cur = 1;                     // 最远的回文的中心位置
   long long ans = 0;
   for (int i = 2; i < n; ++i) {
      int &now = len[i];            // 已 i 为中心的回文半径

      int pos = (cur << 1) - i;                 // 和 i 对称的位置
      now = min(len[pos], cur + len[cur] - i);  // 半径最大不能超出最右边位置
      now = max(now, 0);                        // i 本身已经超出了最右边位置
      while (s[i - now - 1] == s[i + now + 1])
         ++now;
      if (i + now > cur + len[cur])
         cur = i;

      ans += (now + 1) / 2;
   }

   return ans;
}

// ================= 代码实现结束 =================

char _s[N];

int main() {
   scanf("%s", _s + 1);
   printf("%lld\n", getAnswer(_s + 1));
   return 0;
}
