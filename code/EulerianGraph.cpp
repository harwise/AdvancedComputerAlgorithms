/*
 * Eulerian Graph
 *
 * Euler Path: a path which visits each edge exactly once.
 * Euler Tour/Cycle: an Euler path which starts and ends on the same vertex.
 * 
 */

#include "Graph.h"
#include <list>

class EulerianGraph : public Graph {
public:
   bool is_Euler_path() {
      /*
       * Undirected graphs.
       * 1. Connected.
       * 2. All except two vertices have even degrees.
       * 3. at most two vertices has odd degrees.
       * 
       * The Euler path will start from one of these odd degree vertices
       * and ends in the other.
       * 
       * Directed graphs.
       * 1. Connected.
       * 2. Vertices have equal in and out degrees.
       * 3. at most one vertex with indegree - outdegree = 1
       * 4. at most one vertex with outdegree - indegree = 1
       */
   }

   bool is_Euler_tour() {
      /*
       * Undirected graphs.
       * All vertices have even degrees.
       * 
       * Directed graphs.
       * 1. Single SCC (strongly connected component)
       * 2. Vertices have equal in and out degrees.
       */
   }

   void unweighted_Euler_tour() {
      cyc_.clear();
      unweighted_Euler_tour(cyc_.begin(), 0);   // start at verte 0.
      for (auto it = cyc_.begin(); it != cyc_.end(); it++) {
         printf("%d\n", *it);
      }
   }
   void unweighted_Euler_tour(std::list<int>::iterator it, int u) {
      for (int j = 0; j < (int)adjList_[u].size(); j++) {
         ii v = adjList_[u][j];
         if (v.second) {   // weight 0 means used/removed.
            v.second = 0;
            for (int k = 0; k < (int)adjList_[v.first].size(); k++) {
               ii uu = adjList_[v.first][k];    // remove bi-directional eddge
               if (uu.first == u && uu.second) {
                  uu.second = 0;
                  break;
               }
            }
            /*
             * This is why we use list.
             * 把u加进去，处理每一个edge.
             * 在DFS的过程中，前一个edge处理完毕之后；总体形成了一个cycle，但是cycle的终点不一定是u。
             * 退栈回来，我们还需要从u开始再找下一个cycle出来。
             * 并且这个cycle嵌套在第一个cycle之内。
             * 
             *    3-----1------0
             *    |    / \    |
             *    4----   ----2
             * 
             * 
             *    DFS traverse:                 2,1,0    （注意到后面访问的节点是插入到list前面）
             *    unwind to 1:                  2,1,(it)0
             *    insert u and go next edge:    2,1,[1],0
             *    DFS traverse:                 2,1,[3,4,1],0
             */
            unweighted_Euler_tour(cyc_.insert(it, u), v.first);

            /*
             * 通过先遍历子节点，再输入当前节点。可以不用队列。
             * 
             * procedure FindEulerPath(V)
             * 1. iterate through all the edges outgoing from vertex V;
             *       remove this edge from the graph,
             *       and call FindEulerPath from the second end of this edge;
             * 2. add vertex V to the answer.
             */
         }
      }
   }

private:
   std::list<int> cyc_;
};

