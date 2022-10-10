/*
 * Trees
 *
 * 1. Connected undirected graph
 * 2. No cycles =
 *    (n vertices and n-1 edges) =
 *    only unique paths between any two vertices =
 *    (remove any edge and graph becomes disconnected)
 *
 * Rooted Tree - digraph where edges directed away from root
 * Rooting the tree - pick a vertex to be the root. We do this because
 *                    rooted trees are much simpler to deal with.
 * 
 */

#include "Graph.h"

class Tree : public Graph {
public:
   void ap_and_bridge() {
      /*
       * Tree: all internal (non-leaf, degree > 1) vertices are articulation points.
       * Graph: DFS Based.
       */
   }

   void sssp() {
      /*
       * Tree:             O(V)
       * Dijkstra:         O(V + E * logV)
       * Bellman Ford's:   O(V * E)
       */

      // Any traversal.
   }

   void apsp() {
      /*
       * Tree:             O(V * V)
       * Floyd Warshall's: O(V * V * V)
       */

      // Solution 1. Run sssp on every node.
      // Solutoin 2. LCA (lowest common ancestor) See below.
   }

   // Lowest Common Ancestor
   // https://cp-algorithms.com/graph/lca_binary_lifting.html#algorithm
   void lca_binary_lifting_process(int root) {
      /*
       * Preprocessing: O(V*logV)
       * query:         O(logV)
       */
       tin_.resize(V_);
       tout_.resize(V_);
       timer_ = 0;
       l_ = ceil(log2(V_));
       up_.assign(V_, std::vector<int>(l_ + 1));
       dfs_binary_lifting(root, root);
   }
   void dfs_binary_lifting(int v, int p)
   {
      tin_[v] = ++timer_;
      up_[v][0] = p;   // up[i][j] is the 2^j-th ancestor
      for (int i = 1; i <= l_; ++i)
         up_[v][i] = up_[up_[v][i-1]][i-1];
      for (auto u : adjList_[v]) {
         if (u.first != p)
            dfs_binary_lifting(u.first, v);
      }
      tout_[v] = ++timer_;
   }
   int lca_binary_lifting_query(int u, int v) {
      /*
       * Preprocessing: O(N*logN)
       * query:         O(logN)
       */

      /*
       * For each node we will also remember the time of the first visit
       * of this node (i.e. the time when the DFS discovers the node),
       * and the time when we left it (i.e. after we visited all children and
       * exit the DFS function). We can use this information to determine
       * in constant time if a node is an ancestor of another node.
       */
      auto is_ancestor = [this](int u, int v) {
         return tin_[u] <= tin_[v] && tout_[u] >= tout_[v];
      };

      if (is_ancestor(u, v))
         return u;
      if (is_ancestor(v, u))
         return v;
      for (int i = l_; i >= 0; --i) {
         if (!is_ancestor(up_[u][i], v))
            u = up_[u][i];
      }
      return up_[u][0];
   }

   // Lowest Common Ancestor
   // Range Minimum Query: see SparseTable; SegmentTree/FenwickTree.
   // 
   // The key idea is that LCA(u, v) is the shallowest vertex in the tree
   // that is visited between the visits of u and v during a DFS traversal.
   void lca_build_rmq() {
      idx_ = 0;
      memset(H_, -1, sizeof H_);
      lca_dfs(0, 0);
   }
   void lca_dfs(int cur, int depth) {
      H_[cur] = idx_;
      E_[idx_] = cur;
      L_[idx_++] = depth;
      for (int i = 0; i < children_[cur].size(); i++) {
         lca_dfs(children_[cur][i], depth+1);
         /*
          * backtrack to current node.
          * so for each node, (1 + edgecount) times are visited.
          * Over all nodes. _idx is in range [0, V+E) = [0, 2*V-1);
          */
         E_[idx_] = cur;
         L_[idx_++] = depth;
      }
   }

   int diameter() {
      /*
       * Tree: O(V)
       * Graph: Floyd Warshall's O(V * V * V) + all-pairs check O(V * V)
       */

      /*
       * Diameter in a graph
       * -------------------
       *
       * The longest path of all the shortest paths between any two vertices.
       * For general graphs, apply Floyd-warshall's and a for loop. O(n^3)
       * For trees, it's simply the longest path in the tree. Brute force: O(n^2)
       *
       *
       * O(n) algorithm for finding diameter in a tree
       *
       * Algorithm 1. Rooting the tree. +
       *              Precompute the height of every vertex. (DFS) +
       *              Compute and compare the longest paths through roots of every subtree.
       *
       * Alogrithm 2. 1). DFS/BFS from any vertex s to find the furthest vertex x.
       *              2). DFS/BFS one more time from vertex x to get the true furthest vertex y.
       *              The unique path along x to y is the diameter.
       */
   }

   void center() {
      /*
       * Center in a tree
       * ----------------
       *
       * The node(s) that its remoteness is/are the minimal. (A node's remoteness is
       * the distance from its furthest node.)
       *
       * O(n) for finding the center(s): loops that removing all leaf nodes.
       *
       * Properties:
       * 1) All diameters must go through centers.
       * 2) There are at most 2 centers.
       *
       * We can use centers to count/list all the diameters in a tree.
       */
   }

   void centroid() {
      /*
       * Centroid in a tree
       * ------------------
       *
       * When a centroid node is removed, the largest remaining component is minimized,
       * regarding to the subtree size.
       * Center and Centroid are different. Center is measured in distance; centroid is
       * measured in subtree size.
       *
       * O(n) algorithm for finding centroid in a tree
       *
       * Algorithm. Rooting the tree. +
       *            Precompute the subtree size of every node. (DFS) +
       *            Compute and compare the largest remaining subtree size.
       *
       * Properties:
       * 1) Remaining components <= floor(n/2) - good for divide and conquer.
       * 2) There are at most 2 centroids.
       */
   }

   // Minimum Vertex Cover)
   int mvc(int v, int flag) {
      // See DagGraph::tree_mvc
   }

private:
   // for binary lifting
   std::vector<int> tin_;
   std::vector<int> tout_;
   int timer_;
   int l_;
   std::vector<vi> up_;    // up[i][j] is the 2^j-th ancestor

   // for lca_build_rmq
   static constexpr int MAX_N_ = 100;
   int E_[MAX_N_*2];        // the sequence of visisted nodes. idx -> v_index
   int H_[MAX_N_];          // the first occurence of v.       v_index -> idx
   int L_[MAX_N_*2];        // depth of each visit.            idx -> depth
   int idx_;
   std::vector<vi> children_;
};


/*
 * https://github.com/e-maxx-eng/e-maxx-eng/blob/master/src/graph/pruefer_code.md
 *
 * Pr�fer code (or Pr�fer sequence), which is a way of encoding a labeled tree
 * into a sequence of numbers in a unique way.
 *
 * With the help of the Pr�fer code we will prove Cayley's formula
 * (which specified the number of spanning trees in a complete graph).
 * 
 * Also we show the solution to the problem of counting the number of ways of
 * adding edges to a graph to make it connected.
 */

/*
 * Cayley(n) = n^(n-2)
 *
 * Is there a nice formula for counting the number T(n) of unlabeled trees
 * on n vertices? Starting from n = 2 we have T(n) : T(2) = 1, T(3) = 1,
 * T(4) = 2, T(5) = 3.
 * T(n) > Cayley(n) / n!
 * It is an open problem to find a closed form formula for T(n).
 */



