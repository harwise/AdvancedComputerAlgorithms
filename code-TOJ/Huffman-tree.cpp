#include <stdio.h>
#include <stack>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <queue>

using namespace std;


// ================= 代码实现开始 =================

typedef long long ll;

/* 请在这里定义你需要的全局变量 */

priority_queue<ll, vector<ll>, greater<ll>> gHeap;


// 这是求解整个问题的函数
// w：题目描述中的 w（所有）
// n：题目描述中的 n
// 返回值：答案
long long getAnswer(int n, vector<long long> w) {
   /* 请在这里设计你的算法 */
   long long ret = 0;

   for (auto v : w) {
      gHeap.push(v);
   }

   while (gHeap.size() > 1) {
      auto a = gHeap.top();   gHeap.pop();
      auto b = gHeap.top();   gHeap.pop();

      auto c = a + b;   // new subtree
      gHeap.push(c);

      ret += (a + b);
   }

   return ret;
}

// ================= 代码实现结束 =================

int main() {
   int n;
   scanf("%d", &n);
   vector<long long> w;
   for (int i = 0; i < n; ++i) {
      long long x;
      scanf("%lld", &x);
      w.push_back(x);
   }
   printf("%lld\n", getAnswer(n, w));
   return 0;
}
