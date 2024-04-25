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

const int N = 500005, mo = 23333;

/* 请在这里定义你需要的全局变量 */
int f[N], p[N], last[26];

// 为了减少复制开销，我们直接读入信息到全局变量中
// s：题目所给字符串，下标从1开始
// n：字符串长度
int n;
char s[N];

// 求出字符串s有多少不同的子序列
// 返回值：s不同子序列的数量，返回值对mo取模
int getAnswer() {
   /* 请在这里设计你的算法 */
   for (int i = 1; i <= n; ++i) {
      int cnumber = s[i] - 'a';
      p[i] = last[cnumber];
      last[cnumber] = i;
   }

   for (int i = 1; i <= n; ++i) {
      if (p[i] == 0) {
         f[i] = (f[i - 1] * 2 + 1) % mo;
      } else {
         f[i] = (f[i - 1] * 2 - f[p[i] - 1] + mo) % mo;
      }
   }
   return f[n];
}


// ================= 代码实现结束 =================

int main() {
   scanf("%s", s + 1);
   n = strlen(s + 1);
   printf("%d\n", getAnswer());
   return 0;
}
