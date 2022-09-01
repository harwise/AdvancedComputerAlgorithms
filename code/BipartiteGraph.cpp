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
   // Max Cardinality Bipartite Matching
   void mcbm_max_flow() {
      // EK:      O(VEE)
      // Dinic:   O(VVE)
      // MCBM can be reduced to the Max Flow problem.
   }

   // Max Cardinality Bipartite Matching
   int mcbm_alternating_path() {
      /*
       * The blossom algorithm finds a maximum-cardinality matching in general
       * (not necessarily bipartite) graphs. It runs in time O(VVE).
       * 不具有公共端点的边的集合。
       */

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

