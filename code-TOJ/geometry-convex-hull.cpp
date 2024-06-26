﻿#include <stdio.h>
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

typedef long long ll;
const int N = 300005;

// 存储二维平面点
struct ip {
   int x, y, i;
   ip(int x = 0, int y = 0) : x(x), y(y), i(0) { }
   void ri(int _i) {
      scanf("%d%d", &x, &y);
      i = _i;
   }
};

// iv表示一个向量类型，其存储方式和ip一样
typedef ip iv;

// 先比较x轴再比较y轴，
bool operator < (const ip &a, const ip &b) {
   return a.x == b.x ? a.y < b.y : a.x < b.x;
}

// 两点相减得到的向量
iv operator - (const ip &a, const ip &b) {
   return iv(a.x - b.x, a.y - b.y);
}

// 计算a和b的叉积（外积）
ll Cross (const iv &a, const iv &b) {
   return (ll)a.x * b.y - (ll)a.y * b.x;
}

/* 请在这里定义你需要的全局变量 */

// 计算二维点数组a的凸包，将凸包放入b数组中，下标均从0开始
// a, b：如上
// n：表示a中元素个数
// 返回凸包元素个数
int convex(ip *a, ip *b, int n) {
   /* 请在这里设计你的算法 */

   sort(a, a + n);

   int m = 0;

   // upper hull
   for (int i = 0; i < n; ++i) {
      while (m > 1 && Cross(b[m - 1] - b[m - 2], a[i] - b[m - 2]) > 0) {
         m--;
      }
      b[m++] = a[i];
   }

   // lower hull
   int m0 = m;
   for (int i = n - 2; i >= 0; --i) {
      while (m > m0 && Cross(b[m - 1] - b[m - 2], a[i] - b[m - 2]) > 0) {
         m--;
      }
      b[m++] = a[i];
   }

   return m - 1;
}

// ================= 代码实现结束 =================

ip a[N], b[N];

int main() {
   int n;
   scanf("%d", &n);
   for (int i = 0; i < n; ++i)
      a[i].ri(i + 1);
   int m = convex(a, b, n), ans = m;
   for (int i = 0; i < m; ++i)
      ans = ((ll)ans * b[i].i) % (n + 1);
   printf("%d\n", ans);
   return 0;
}
