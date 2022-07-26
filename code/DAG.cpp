/*
 * DAGs
 *
 * 1. Directed
 * 2. No cycles
 * 
 * Suitable for DP technique.
 * --------------------------
 * DP states: vertices in implicit DAG.
 * Transitions: directed edges.
 * overlapping problems: topological sort of this DAG allows each overlapping
 *                       subproblem (sub graph of the DAG) to be processed
 *                       just once.
 * 
 * 
 * Converting General Graph to DAG
 * -------------------------------
 * (General Graph Node, parameter) = DAG node.
 * 
 * E.g. the parameter can be
 * 1. time
 * 2. decreasing value
 * Nodes in both examples go in one direction (time can only go further), so
 * DAGs are modeled.
 * 
 */

#include <vector>

typedef std::vector<int> vi;


class DagGraph {
public:
   // Single-Source Shortest Path
   void sssp() {
      /*
       * DAG:              O(V + E)
       * Dijkstra:         O(V + E * logV)
       * Bellman Ford's:   O(V * E)
       */

      // Bottom-Up DP
      // 1. topological sort
      // 2. relax the edges according to this order.

      // Top-Down DP
      // Easy
   }

   // Single Source Longest (Simple) Path
   void sslp() {
      /*
       * DAG:              O(V + E)
       * General:          The decision version is NP-Complete
       */
      // 1. edge weigt *= -1
      // 2. sssp
   }

   // count paths in DAG
   int numPaths() {
      // Bottom-Up DP
      // 1. topological sort
      // 2. Bottom-Up DP (num_paths[cur_neighbor] += num_paths[cur])

      // Top-Down DP
      // Easy
   }

   // Minimum Vertex Cover (on a Tree)
   int tree_mvc(int v, int flag) {
      if (memo_[v][flag] != -1) {
         return memo_[v][flag];
      }

      int ans = 0;
      if (leaf_[v]) {
         ans = flag;       // 1/0 = taken/not
      } else if (flag == 0) {
         /*
          * if v is not taken, we must take its children.
          */
         ans = 0;
         for (int j = 0; j < (int)children_[v].size(); j++) {
            ans += tree_mvc(children_[v][j], 1);
         }
      } else { // flag == 1
         /*
          * if v is taken, taken the minimum between taking or not taking
          * its children.
          */
         ans = 1;
         for (int j = 0; j < (int)children_[v].size(); j++) {
            ans += std::min(tree_mvc(children_[v][j], 1),
                            tree_mvc(children_[v][j], 0));
         }
      }
      return memo_[v][flag] = ans;
   }

   // Min Path Cover
   int mpc() {
      // See BipartiteGraph::dag_mpc
   }

private:
   int memo_[100][2];
   int leaf_[100];
   vi children_[100];
};
