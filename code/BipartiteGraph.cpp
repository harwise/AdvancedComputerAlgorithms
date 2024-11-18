/*
 * Bipartite Graph
 *
 * V can be partitioned into two disjoint sets V1 and V2.
 * All edges (u, v) has the property that u is in V1 and v is in V2.
 * 
 * Free from odd-length cycle.
 * Trees is also bipartite graphs.
 * 
 */

#include "Graph.h"

class BipartiteGraph : public Graph {
public:

   // MCBM: Max Cardinality Bipartite Matching
   /*
    * Can only apply to Unweighted MCBM.
    * 
    * Hungarian algorithm.
    * 1. 为什么找不到增广路就一定是最大匹配了？
    *    假设通过此算法得到的匹配不是最大匹配，前者为H，后者为B。
    *    构造一条路径，从 B 的一个点出发，B 和 H 的边交替出现。
    *    通过这种路径的关键特性，能够得到 V(H) >= V(B)，与假设矛盾。
    * 
    * 2. 为什么只遍历一次就够了？
    *    因为一条增广路，如果后面能找到的话，前面一定也能（更能）找到。
    */
   int mcbm_alternating_path() {
      // O(VV+VE)
      int cardinality = 0;
      owner_.assign(V_, -1);
      for (int left = 0; left < num_vertices_on_left_; left++) {
         visited_.assign(num_vertices_on_left_, 0);
         cardinality += mcbm_alternating_path(left);
      }
      printf("Found %d matchings\n", cardinality);
      return cardinality;
   }
   int mcbm_alternating_path(int left) {
      if (visited_[left])
         return 0;
      visited_[left] = true;
      for (int j = 0; j < (int)adjList_[left].size(); j++) {
         ii right = adjList_[left][j];
         // Go until a free right node is found.
         if (owner_[right.first] == -1 ||
             mcbm_alternating_path(owner_[right.first])) {
            owner_[right.first] = left;
            return 1;
         }
      }
      return 0;
   }

   // MCBM: Max Cardinality Bipartite Matching
   /*
    * Can only apply to Unweighted MCBM.
    * Based on the Augmenting Path algorithm, but explores the shorter path
    * augumenting path first. It is proved that in this way only O(sqrt(v))
    * iterations is required.
    */
   int mcbm_Hopcroft_Karp() {
      // O(sqrt(V)*E)
      // TODO
      return 0;
   }

   // MCBM: Max Cardinality Bipartite Matching
   /*
    * Weighted MCBM can be reduced to MCMF (Min Cost Max Flow)
    */
   void mcbm_max_flow() {
      // EK:      O(VEE)
      // Dinic:   O(VVE)
      // MCBM can be reduced to the Max Flow problem.
   }

   /*
    * Kuhn-Munkres’s Hungarian algorithm
    * Get perfect bipartite matching with minimum cost.
    */
   void mcbm_Kuhn_Munkres() {
      // TODO
   }

   // Max Independent Set (of vertices)
   /*
    * Every edge has at least one edpoint NOT in S;
    * Every v not in S has at least one neighbour in S.
    */
   int mis() {
      /*
       * General graphs: based on Maximum-Cardinality Matching, O(VVE)
       */

      return V_ - mcbm_alternating_path();
   }

   // Min Vertex Cover
   int mvc() {
      /*
       * General graphs: NP-Complete.
       */

      return mcbm_alternating_path();
   }

   // Min Path Cover
   int dag_mpc() {
      // MPC on general graphs: NP-Complete

      // DAG G(V, E) -> Bipartite G'(V',E')
      /*
       * G' = (V_OUT + V_IN, E')
       * V_OUT = v in G that has positive out-degree
       * V_IN = v that has positive-indegree
       * E' = all edges from V_IN to V_OUT
       * 
       * Imagine we have no edge at all, then we need V vertices/paths
       * to cover all vertices.
       * Vertices must not be shared in MPC, so one matching on G' means
       * two vertices on G can be grouped on a path.
       * return (V_ - MCBM on G').
       * 
       */
   }

private:
   vi owner_;     // the left node that owns/matches the right node 
   vi visited_;
   int num_vertices_on_left_;
};

