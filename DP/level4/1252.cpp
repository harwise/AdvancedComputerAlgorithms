#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

int M, N;
int F[128];

/*
 * Q: 考察这些问题组成的子集
 * A: 对这些问题的回答，每个问题回答0/1
 * dp[Q][A]: 基于这个Q/A组合，至少需要继续问多少问题，才能把所有相关的objects都找出来。
 *           相关的是指，能满足现在的Q/A组合的所有objects。
 */
int dp[1 << 11][1 << 11];

/*
 * 虽然对于一个object来说，每一个问题/feature都是独立的，先问哪个后问哪个没有区别，
 * 但是许多个objects放到一起考虑，要把他们区分出来，先后顺序是关键。比如：
 * 1 0 0 0 1
 * 1 0 0 1 0
 * 0 0 1 0 0
 * 0 1 0 0 0
 * 先问第一个问题，可以两步就都区分出来；
 * 先问其它问题，都需要三步或以上。
 */

// Q: bitmask of questions.
// A: bitmask of answers.
int search(int Q, int A)
{
    if (dp[Q][A] != -1)
        return dp[Q][A];

    // If the number of remained objects are less than 2, then there is no
    // need to ask any other questions.
    int nObjects = 0;
    for (int i = 0; i < N; ++i)
        if ((F[i] & Q) == A)
            ++nObjects;

    // n == 0: 增加了一个问题&回答后，没有任何object符合A这个回答组合。（没增加这个问题&回答之前，是有多个objects符合的，所以n=0这种情况一定比n=1的情况更早退栈。）
    // n == 1: 在问了Q这么多问题之后，A这个回答组合，能够唯一确定了一个object。
    if (nObjects <= 1)
        return dp[Q][A] = 0;

    // Try to ask each question and check its maximum number of required 
    // questions to identify the remained objects. Pick the minimum of them.
    /*
     * Q/A这个组合对应了多个objects，还需要多问问题才能区分出来。
     * 先问哪一个问题是关键。我们遍历所有情况，取最优/min的那一个。
     *
     * dp[i][j]对于所有方案的值都是相同的，那为什么问题要有先后之分呢：
     * 之前问问题的先后顺序，决定这一步，回答是与回答否，这两个分支，对应到不同的dp[k][l]组合关系。
     * 比如：
     * 对于1和4两个问题，mask=1001.
     * 如果先问1，1000/0000
     *               ------1001/0000
     *               ------1001/0001
     *           1000/1000
     *               ------1001/1000
     *               ------1001/1001
     * 如果先问4，0001/0000
     *               ------1001/0000
     *               ------1001/1000
     *           0001/0001
     *               ------1001/0001
     *               ------1001/1001
     * 
     * 本质上还是树结构的平衡问题。
     */
    int nQuestions = M + 1;
    for (int i = 0; i < M; ++i)
        if ((Q & (1 << i)) == 0)
            /*
             * 基于已经问过的问题Q基础上，再问一个新问题。于是递归深度加1。
             * 回答是0/1两种情况，会将objects再分成两部分。每一部分都需要再进一步区分，
             * 所以取两者的最大值。
             */
            nQuestions = min(nQuestions, 1 + max(search(Q | (1 << i), A),                   // 回答是0，能找出哪些objects
                                                 search(Q | (1 << i), A | (1 << i))));      // 回答是1，能找出另外那些objects

    return dp[Q][A] = nQuestions;
}

int solve()
{
    memset(dp, -1, sizeof(dp));
    return search(0, 0);
}

int main()
{
    while (cin >> M >> N, !(M == 0 && N == 0))
    {
        for (int i = 0; i < N; ++i)
        {
            string s;
            cin >> s;
            
            int feature = 0;
            for (int j = 0; j < M; ++j)
                feature |= (s[j] - '0') << j;
            
            F[i] = feature;
        }
        cout << solve() << endl;
    }
    return 0;
}
