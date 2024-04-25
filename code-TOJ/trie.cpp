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

const int M = 505, L = 1000005;

// c：trie树上的边，c[x][y]表示从节点x出发（x从1开始），字符为y的边（y范围是0到25）
// sz：sz[x]表示x节点的子树中终止节点的数量（子树包括x自身）
// cnt：trie树上节点的数目
int c[L][26], sz[L], cnt;

// 将字符串s加入到trie树中
// s：所要插入的字符串
void add(char *s) {
   /* 请在这里设计你的算法 */
   int node = 0;
   sz[node] += 1;
   for (int i = 0; s[i]; ++i) {
      if (c[node][s[i] - 'a'] == 0) {
         c[node][s[i] - 'a'] = (++cnt);
      }
      node = c[node][s[i] - 'a'];
      sz[node] += 1;
   }
}

// 用于计算sz数组
// x：当前节点
void dfs(int x) {
   /* 请在这里设计你的算法 */
}

// 用字符串s沿着trie树上走，找到相应的节点
// s：所给字符串
// 返回值：走到的节点
int walk(char *s) {
   /* 请在这里设计你的算法 */
   int node = 0;
   for (int i = 0; s[i]; ++i) {
      if (c[node][s[i] - 'a'] == 0) {
         return 0;
      }
      node = c[node][s[i] - 'a'];
   }
   return node;
}

// ================= 代码实现结束 =================

char s[M];

int main() {
   int n, m;
   scanf("%d%d", &n, &m);
   for (; n--;) {
      scanf("%s", s);
      add(s);
   }
   dfs(0);
   sz[0] = 0;
   for (; m--;) {
      scanf("%s", s);
      printf("%d\n", sz[walk(s)]);
   }
   return 0;
}
