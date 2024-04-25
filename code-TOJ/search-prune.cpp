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
int ans, allOne;

void dfs(int pos, int left, int right)
{
	if (pos == allOne)
	{
		++ans;
		return;
	}
	int t = allOne & ~(pos | left | right);
	while (t) {
		int p = t & (~t + 1);
		dfs(pos | p, (left | p) << 1, (right | p) >> 1);
		t ^= p;
	}

}

// 一个n×n的棋盘，在棋盘上摆n个皇后，求满足任意两个皇后不能在同一行、同一列或同一斜线上的方案数
// n：上述n
// 返回值：方案数
int getAnswer(int n) {
	/* 请在这里设计你的算法 */
	ans = 0;
	allOne = (1 << n) - 1;
	dfs(0, 0, 0);
	return ans;
}

// ================= 代码实现结束 =================

int main() {
	int n;
	cin >> n;
	cout << getAnswer(n) << endl;
	return 0;
}
