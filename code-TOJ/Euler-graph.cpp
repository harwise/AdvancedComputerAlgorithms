#include <stdio.h>
#include <stack>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <queue>

using namespace std;

// ================= 代码实现开始 =================

int allOne;
vector<bool> vis[2];    // 2^(n - 1) 个节点，出去的边有两条(节点二进制末尾添加 0 或 1)
string ans;

constexpr int twoPow(int x)
{
   return 1 << x;
}

void dfs(int u)
{
   for (int i = 0; i < 2; ++i) {
      if (!vis[i][u]) {
         int v = ((u << 1) | i) & allOne;    // 下一个节点
         vis[i][u] = true;

         dfs(v);
         ans += (i == 0 ? "0" : "1");
      }
   }
}

/* 请在这里定义你需要的全局变量 */

// 本函数求解大转盘上的数，你需要把大转盘上的数按顺时针顺序返回
// n：对应转盘大小，意义与题目描述一致，具体见题目描述。
// 返回值：将大转盘上的数按顺时针顺序放到一个string中并返回
string getAnswer(int n) {
   /* 请在这里设计你的算法 */
   allOne = twoPow(n - 1) - 1;
   ans = "";
   vis[0].resize(twoPow(n - 1), 0);    // 2^(n - 1) 个节点
   vis[1].resize(twoPow(n - 1), 0);

   dfs(0);
   return ans;
}

// ================= 代码实现结束 =================

int main() {
   int n;
   scanf("%d", &n);
   cout << getAnswer(n) << endl;
   return 0;
}
