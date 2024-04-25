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

/* 请在这里定义你需要的全局变量 */

vector<int> Next;    // KMP: Next Table

// 这是匹配函数，将所有匹配位置求出并返回
// n：串 A 的长度
// A：题目描述中的串 A
// m：串 B 的长度
// B：题目描述中的串 B
// 返回值：一个 vector<int>，从小到大依次存放各匹配位置
vector<int> match(int n, string A, int m, string P) {
   /* 请在这里设计你的算法 */

   Next.resize(m);

   int t = Next[0] = -1;
   int j = 0;
   while (j < m - 1) {
      if (t < 0 || P[j] == P[t]) {
         Next[++j] = ++t;
      } else {
         t = Next[t];
      }
   }

   vector<int> ret;

   int i = 0;
   j = 0;
   while (j < m && i < n) {
      if (j < 0 || A[i] == P[j]) {
         if (j == m - 1) {
            ret.push_back(i - j);
            j = Next[j];            // 和最后一个没匹配上的逻辑完全相同。
         } else {
            i++; j++;
         }
      } else {
         j = Next[j];
      }
   }

   return ret;
}

// ================= 代码实现结束 =================

int main() {
   ios::sync_with_stdio(false);
   int n, m;
   string A, B;
   cin >> n >> A;
   cin >> m >> B;
   vector<int> ans = match(n, A, m, B);
   for (vector<int>::iterator it = ans.begin(); it != ans.end(); ++it)
      cout << *it << '\n';
   return 0;
}
