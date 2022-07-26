/*
 * Tree Traversal Trickery
 *
 * Preorder and Postorder numbers
 * ------------------------------
 * 
 * # [preorder, postorder] interval. Tree linearization.
 *   Nested interval structure. Child's interval is nested in its parent's.
 * # The preorder&postorder sequence <-> parenthesis statement.
 *   E.g. [Root Node]pre-1 (, [Left Node]pre-2 (, [Left Node]post-3 ),
 *        [Right Node]pre-4 (, [Right Node]post-5 ), [Root Node]post-6 ).
 * 
 * Tree linearization
 * ------------------
 * 
 * # Subtree query -> range sum -> Fenwick tree
 * 
 * Quiz: Sum Query on Subtrees
 * ---------------------------
 * 
 * 1. Values at nodes
 * 2. Update values
 * 3. Query subtree sum
 * 
 * Solution 1: update O(1); query O(n) with DFS
 * Solution 2: Store subtree sums at nodes (But can we change the node itself?).
 *             update O(log(n)); query O(1)
 * Solution 3: linearization and store values at preorders.
 *             update O(log(n)); query O(log(n))
 *
 * Quiz: Family Fortune
 * ---------------------------
 * 
 * 1. A tree (n <= 10^5) with every node having a value.
 * 2. Select k nodes (k <= 1000), which are not ancestors of each other.
 * 3. To make the sum of values maximum.
 * 
 * Solution 1: Tree DP. dp[parent] = f(dp[child0], dp[child1], ...). O(nk^2)
 * Solution 2: Linearization + Knapsack style DP.
 *             State (i, k).
 *             Transitions. 1. take reward (i=i+jump); 2. i=i+1. (nk)
 * 
 */

#include <vector>
#include <limits>
#include <algorithm>

class FamilyFortuneKnapscak
{
public:
   FamilyFortuneKnapscak()
   {
      N_ = 3;
      K_ = 2;
      adj_.resize(3);
      adj_[0].push_back(1);
      adj_[0].push_back(2);
      invp_.resize(3);
      jump_.resize(3);

      reward_.push_back(2);
      reward_.push_back(3);
      reward_.push_back(5);
   }

   void dfs(int i)
   {
      int pre = counter_++;
      invp_[pre] = i;

      for (int j : adj_[i]) {
         dfs(j);
      }

      jump_[pre] = counter_;
   }

   int Solve()
   {
      dfs(0);

      std::vector<int> cur(N_+1, std::numeric_limits<int>::min());
      cur[0] = 0;
      for (int k = 0; k < K_; k++) {
         std::vector<int> nxt(N_+1, std::numeric_limits<int>::min());
         for (int i = 0; i < N_; i++) {
            // state - (i, k)
            // i - preorder number
            // k - taken k nodes so far

            // (i, k) -> (i+1, k)
            cur[i+1] = std::max(cur[i+1], cur[i]);

            // (i, k) -> (jump(i), k+1)
            nxt[jump_[i]] = std::max(nxt[jump_[i]], cur[i] + reward_[invp_[i]]);
         }
         cur = nxt;
      }

      return *(std::max_element(cur.begin(), cur.end()));
   }

private:
   std::vector<std::vector<int>> adj_;
   std::vector<int> reward_;  // node -> value
   std::vector<int> invp_; // preorder -> node
   std::vector<int> jump_; // preorder -> next preorder when this subtree is skipped.
   int counter_ = 0;
   int N_ = 0;
   int K_ = 0;
};


class FamilyFortuneTreeDp
{
public:
   FamilyFortuneTreeDp()
   {
      N_ = 3;
      K_ = 2;
      adj_.resize(3);
      adj_[0].push_back(1);
      adj_[0].push_back(2);

      reward_.push_back(2);
      reward_.push_back(3);
      reward_.push_back(5);
   }

   // return the table mapping k -> max sum for subtree/node i
   std::vector<int> go(int i)
   {
      std::vector<int> dp(K_+1, std::numeric_limits<int>::min());
      dp[0] = 0;
      dp[1] = reward_[i];

      for (int j : adj_[i]) {                      // N
         auto dp2 = go(j);
         for (int k = 0; k < K_; ++k) {            // N*K
            for (int k1 = 1; k1 < k; k1++) {       // N*K*K
               if (dp[k1] == std::numeric_limits<int>::min()) break;
               int k2 = k - k1;
               // WRONG! dp table is overwritten. We should fill dp backward.
               dp[k] = std::max(dp[k], dp2[k1] + dp[k2]);
            }
         }
      }

      return dp;
   }

   int Solve()
   {
      auto res = go(0);
      return res[K_] > 0 ? res[K_] : 0;
   }

private:
   std::vector<std::vector<int>> adj_;
   std::vector<int> reward_;  // node -> value
   int N_ = 0;
   int K_ = 0;
};
