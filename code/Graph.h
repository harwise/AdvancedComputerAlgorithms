#include "UnionFindDisjointSet.h"
#include <utility>
#include <vector>
#include <map>
#include <queue>
#include <iostream>

#define DFS_WHITE -1
#define DFS_BLACK 1
#define DFS_GRAY 2

typedef std::pair<int, int> ii;
typedef std::vector<ii> vii;
typedef std::vector<int> vi;

class Graph
{
public:
   void dfs(int u) {
      dfs_num_[u] = DFS_BLACK;
      printf(" %d", u);
      for (int j = 0; j < (int)adjList_[u].size(); ++j) {
         ii v = adjList_[u][j];
         if (dfs_num_[v.first] == DFS_WHITE) {
            dfs(v.first);
         }
      }
   }

   void bfs(int s) {
      vi dist(V_, -1);
      dist[s] = 0;
      std::queue<int> q;
      q.push(s);
      while (!q.empty()) {
         int u = q.front();
         q.pop();
         for (int j = 0; j < (int)adjList_[u].size(); ++j) {
            ii v = adjList_[u][j];
            if (dist[v.first] == -1) {
               dist[v.first] = dist[u] + 1;
               q.push(v.first);
            }
         }
      }
   }

   // connected components
   void undirected_cc() {
      int numCC = 0;
      dfs_num_.assign(V_, DFS_WHITE);
      for (int i = 0; i < V_; ++i) {
         if (dfs_num_[i] == DFS_WHITE) {
            printf("Component %d:", ++numCC);
            dfs(i);
            printf("\n");
         }
      }
      printf("There are %d CC.\n", numCC);
   }

   int floodfill(int r, int c, char c1, char c2) {
      static int dr[] = {1,1,0,-1,-1,-1,0,1};
      static int dc[] = {0,1,1,1,0,-1,-1,-1};

      if (r < 0 || r >= R_ || c < 0 || c >= C_) {
         return 0;
      }
      if (grid_[r][c] != c1) {
         return 0;
      }
      int ans = 1;
      grid_[r][c] = c2;
      for (int d = 0; d < 8; d++) {
         ans += floodfill(r + dr[d], c + dc[d], c1, c2);
      }
      return ans;
   }

   // topological sort
   void dfs2(int u) {
      dfs_num_[u] = DFS_BLACK;
      for (int j = 0; j < (int)adjList_[u].size(); ++j) {
         ii v = adjList_[u][j];
         if (dfs_num_[v.first] == DFS_WHITE) {
            dfs2(v.first);
         }
      }
      topoSort_.push_back(u);       // post-order!
   }
   void topoSort() {
      topoSort_.clear();
      dfs_num_.assign(V_, DFS_WHITE);
      for (int i = 0; i < V_; ++i) {
         if (dfs_num_[i] == DFS_WHITE) {
            dfs2(i);
         }
      }
      std::reverse(topoSort_.begin(), topoSort_.end());
      std::cout << topoSort;
   }

   bool isBipartite(int s) {
      vi dist(V_, -1);
      dist[s] = 0;
      std::queue<int> q;
      q.push(s);

      bool isBip = true;
      while (!q.empty()) {
         int u = q.front();
         q.pop();
         for (int j = 0; j < (int)adjList_[u].size(); ++j) {
            ii v = adjList_[u][j];
            if (dist[v.first] == -1) {
               dist[v.first] = 1 - dist[u];     // 0 <-> 1
               q.push(v.first);
            } else if (dist[v.first] == dist[u]) {
               isBip = false;
            }
         }
      }
      return isBip;
   }

   // edge types in DFS spanning tree
   void graphCheck(int u) {
      dfs_num_[u] = DFS_GRAY;       // start the sub-tree
      for (int j = 0; j < (int)adjList_[u].size(); ++j) {
         ii v = adjList_[u][j];
         if (dfs_num_[v.first] == DFS_WHITE) {
            dfs_parent_[v.first] = u;
            graphCheck(v.first);
         } else if (dfs_num_[v.first] == DFS_GRAY) {
            if (v.first == dfs_parent_[u]) {
               printf("Bidirectional (%d, %d) - (%d, %d)\n",
                      u, v.first, v.first, u);
            } else {
               printf("Back Edge (%d, %d) (Cycle)\n", u, v.first);
            }
         } else if (dfs_num_[v.first] == DFS_BLACK) {    // directional graph only
            printf("Forward/Cross Edge (%d, %d)\n", u, v.first);
         }
      }
      dfs_num_[u] = DFS_BLACK;      // finish the sub-tree
   }
   void graphCheck() {
      dfs_num_.assign(V_, DFS_WHITE);
      dfs_parent_.assign(V_, 0);
      int numComp = 0;
      for (int i = 0; i < V_; ++i) {
         if (dfs_num_[i] == DFS_WHITE) {
            printf("Component %d:\n", ++numComp);
            graphCheck(i);
         }
      }
   }

   // Articulation Points and Bridges
   void undirected_ap_and_bridge(int u, int dfsRoot, int& rootChildren, vi& articulation_vertex) {
      dfs_low_[u] = dfs_num_[u] = dfsNumberCounter_++;
      for (int j = 0; j < adjList_[u].size(); ++j) {
         ii v = adjList_[u][j];
         if (dfs_num_[v.first] == DFS_WHITE) {  // -1
            dfs_parent_[v.first] = u;
            if (u == dfsRoot) {
               rootChildren++;
            }

            undirected_ap_and_bridge(v.first, dfsRoot, rootChildren, articulation_vertex);

            if (dfs_low_[v.first] >= dfs_num_[u]) {
               articulation_vertex[u] = true;
            }
            if (dfs_low_[v.first] > dfs_num_[u]) {
               printf("Edge (%d, %d) is a bridge\n", u, v.first);
            }
            dfs_low_[u] = std::min(dfs_low_[u], dfs_low_[v.first]);
         } else if (v.first != dfs_parent_[u]) {   // a back edge but not bi-directional.
            dfs_low_[u] = std::min(dfs_low_[u], dfs_low_[v.first]);
         }
      }
   }
   void undirected_ap_and_bridge() {
      dfsNumberCounter_ = 0;
      dfs_num_.assign(V_, DFS_WHITE);
      dfs_low_.assign(V_, 0);
      dfs_parent_.assign(V_, 0);
      vi articulation_vertex(V_, 0);
      printf("Bridges:\n");
      for (int i = 0; i < V_; ++i) {
         if (dfs_num_[i] == DFS_WHITE) {
            int dfsRoot = i;
            int rootChildren = 0;
            undirected_ap_and_bridge(i, dfsRoot, rootChildren, articulation_vertex);
            articulation_vertex[i] = (rootChildren > 1);
         }
      }
      printf("Articulation Points:\n");
      for (int i = 0; i < V_; ++i) {
         if (articulation_vertex[i]) {
            printf("Vertex %d\n", i);
         }
      }
   }

   // strongly connected component
   void directed_tarjan_scc(int u, vi& S, vi& visited, int& numSCC) {
      dfs_low_[u] = dfs_num_[u] = dfsNumberCounter_++;
      S.push_back(u);
      visited[u] = 1;
      for (int j = 0; j < adjList_[u].size(); ++j) {
         ii v = adjList_[u][j];
         if (dfs_num_[v.first] == DFS_WHITE) {
            directed_tarjan_scc(v.first, S, visited, numSCC);
         }
         // Vetices in having-found SCCs are excluded by this check.
         if (visited[v.first]) {
            dfs_low_[u] = std::min(dfs_low_[u], dfs_low_[v.first]);
         }
      }

      if (dfs_low_[u] == dfs_num_[u]) {   // a root of an SCC
         printf("SCC %d", ++numSCC);
         while (true) {
            int v = S.back();
            S.pop_back();
            // This vertex is Excluded when we continue finding other SCCs.
            visited[v] = 0;
            printf(" %d", v);
            if (u == v) break;
         }
      }
      printf("\n");
   }
   void directed_tarjan_scc() {
      dfs_num_.assign(V_, DFS_WHITE);
      dfs_low_.assign(V_, 0);
      vi visited(V_, 0);
      dfsNumberCounter_ = 0;
      int numSCC = 0;
      vi S;
      for (int i = 0; i < V_; ++i) {
         if (dfs_num_[i] == DFS_WHITE) {
            directed_tarjan_scc(i, S, visited, numSCC);
         }
      }
   }


protected:
   int V_;
   int E_;
   std::vector<vii> adjList_;
   int dfsNumberCounter_;
   vi dfs_num_;
   vi dfs_low_;
   vi dfs_parent_;
   vi topoSort_;

   // grid: implict graph
   int R_;
   int C_;
   std::vector<vi> grid_;
};


// Minimum Spanning Tree
class GraphMst : public Graph
{
public:
   void kruskal_mst() {
      std::vector<std::pair<int, ii>> edgeList; // weight, vi, vj
      for (int i = 0; i < E_; ++i) {
         int a, b, weight;
         scanf("%d %d %d", &a, &b, &weight);
         edgeList.push_back(std::make_pair(weight, ii(a,b)));
      }
      std::sort(edgeList.begin(), edgeList.end());

      int mst_cost = 0;
      UnionFindDisjointSet ufds;
      ufds.initSet(V_);
      for (int i = 0; i < E_; ++i) {
         auto front = edgeList[i];
         if (!ufds.isSameSet(front.second.first, front.second.second)) {
            mst_cost += front.first;
            ufds.unionSet(front.second.first, front.second.second);
         }
      }
      printf("MST cost = %d\n", mst_cost);
   }

   void prim_mst() {
      vi taken;
      std::priority_queue<ii> pq;

      auto process = [this, &taken, &pq](int vtx) {
         taken[vtx] = 1;
         for (int j = 0; j < adjList_[vtx].size(); j++) {
            ii v = adjList_[vtx][j];
            if (!taken[v.first]) {
               // sort by (inc) weight then by (inc) id
               // by using -ve sign to reverse order
               pq.push(ii(-v.second, -v.first));
            }
         }
      };

      taken.assign(V_, 0);
      process(0);
      int mst_cost = 0;
      while (!pq.empty()) {
         ii front = pq.top();
         pq.pop();
         if (!taken[-front.second]) {
            mst_cost += -front.first;
            process(-front.second);
         }
      }
      printf("MST cost = %d\n", mst_cost);
   }
};


// Single Source Shortest Path
class GraphSssp : public Graph
{
public:
   // Adds a few lines on bfs.
   void unweight_sssp(int s) {
      vi dist(V_, -1);
      dist[s] = 0;
      std::queue<int> q;
      q.push(s);
      //vi p;                         // the parent vector.
      while (!q.empty()) {
         int u = q.front();
         q.pop();
         for (int j = 0; j < (int)adjList_[u].size(); ++j) {
            ii v = adjList_[u][j];
            if (dist[v.first] == -1) {
               dist[v.first] = dist[u] + 1;
               p_[v.first] = u;      // the parent of v.first is u.
               q.push(v.first);
            }
         }
      }
      // PrintPath(s, t);              // print the shortest path from s to t.
   }
   void printPath(int s, int u) {
      if (u == s) {
         printf("%d", s);
         return;
      }
      printPath(s, p_[u]);
      printf(" %d", u);
   }

   void weighted_dijkstra_sssp(int s) {
      int INF = 1e9;;
      vi dist(V_, INF);
      dist[s] = 0;
      std::priority_queue<ii, std::vector<ii>, std::greater<ii>> pq;
      pq.push(ii(0, s));
      while (!pq.empty()) {
         ii front = pq.top(); pq.pop();
         int d = front.first;
         int u = front.second;
         if (d != dist[u]) {
            continue;
         }
         for (int j = 0; j < (int)adjList_[u].size(); j++) {
            ii v = adjList_[u][j];
            if (dist[u] + v.second < dist[v.first]) {
               dist[v.first] = dist[u] + v.second;
               pq.push(ii(dist[v.first], v.first));
            }
         }
      }
   }

   void negative_cycle_bellman_ford_sssp(int s) {
      int INF = 1e9;
      vi dist(V_, INF);
      dist[s] = 0;
      for (int i = 0; i < V_ - 1; i++) {  // relax all edges V-1 times.
         for (int u = 0; u < V_; u++) {
            for (int j = 0; j < (int)adjList_[u].size(); j++) {
               ii v = adjList_[u][j];
               dist[v.first] = std::min(dist[v.first], dist[u] + v.second);
            }
         }
      }

      bool hasNegativecycle = false;
      for (int u = 0; u < V_; u++) {
         for (int j = 0; j < (int)adjList_[u].size(); j++) {
            ii v = adjList_[u][j];
            if (dist[v.first] > dist[u] + v.second) {
               hasNegativecycle = true;
            }
         }
      }
      printf("Negative Cycle Exist? %s\n", hasNegativecycle ? "Yes" : "No");
   }

private:
   vi p_;      // the parent vector.
};


// All Pairs Shortest Path
class GraphApsp : public Graph
{
public:
   void floyd_warshall_apsp() {
      for (int k = 0; k < V_; k++) {   // DP: i->(0,...,k)->j
         for (int i = 0; i < V_; i++) {
            for (int j = 0; j < V_; j++) {
               adjMat_[i][j] = std::min(adjMat_[i][j],
                                        adjMat_[i][k] + adjMat_[k][j]);
            }
         }
      }
   }

   void floyd_warshall_apsp_path() {
      for (int i = 0; i < V_; i++) {
         for (int j = 0; j < V_; j++) {
            p_[i][j] = i;
         }
      }

      for (int k = 0; k < V_; k++) {   // DP: i->(0,...,k)->j
         for (int i = 0; i < V_; i++) {
            for (int j = 0; j < V_; j++) {
               if (adjMat_[i][k] + adjMat_[k][j] < adjMat_[i][j]) {
                  adjMat_[i][j] = adjMat_[i][k] + adjMat_[k][j];
                  p_[i][j] = p_[k][j];
               }
            }
         }
      }
   }

   void floyd_warshall_transitive_closure() {
      for (int k = 0; k < V_; k++) {   // DP: i->(0,...,k)->j
         for (int i = 0; i < V_; i++) {
            for (int j = 0; j < V_; j++) {
               transitiveMat_[i][j] =
                  transitiveMat_[i][j] |
                  (transitiveMat_[i][k] & transitiveMat_[k][j]);
            }
         }
      }
   }

   void floyd_warshall_minimax() {
      for (int k = 0; k < V_; k++) {   // DP: i->(0,...,k)->j
         for (int i = 0; i < V_; i++) {
            for (int j = 0; j < V_; j++) {
               minimaxMat_[i][j] = std::min(
                  minimaxMat_[i][j],
                  std::max(minimaxMat_[i][k], minimaxMat_[k][j]));
            }
         }
      }
   }

private:
   std::vector<vi> adjMat_;       // ajdMat_[i][j] is the weight of edge (i, j)
   std::vector<vi> p_;            // p_[i][j]: i -> ... -> p[i][j] -> j
   std::vector<vi> transitiveMat_;// d[i][j] is transitive or not
   std::vector<vi> minimaxMat_;   // d[i][j] is the minimax cost
};


class GraphMaxFlow : public Graph
{
public:
   void ford_fulkerson() {
      // residual graph
      // mf = 0
      // while (there exists an augmenting path p from s to t) {
      //    // p is a path from s to t that pass through positive edges in residual graph
      //    augment/send flow f along the path p
      //       1. find f, the minimum edge weight along the path p
      //       2. decrease the residual capacity of forward edges along path p by f.
      //       3. increate the residual capacity of backward edges along path p by f.
      //    mf += f
      // }
      // output mf
   }

   // ford_fulkerson + BFS
   int edmonds_karp(int s, int t) {
      int flow = 0;
      std::vector<int> parent(V_);

      while (int new_flow = edmonds_karp_bfs(s, t, parent)) {
         flow += new_flow;
         int cur = t;
         while (cur != s) {
            int prev = parent[cur];
            res_[prev][cur] -= new_flow;
            res_[cur][prev] += new_flow;
            cur = prev;
         }
      }
   }
   int edmonds_karp_bfs(int s, int t, std::vector<int> &parent) {
       int INF = 1e9;;
       std::fill(parent.begin(), parent.end(), -1);
       parent[s] = -2;
       std::queue<ii> q;
       q.push({s, INF});

       while (!q.empty()) {
           int cur = q.front().first;
           int flow = q.front().second;
           q.pop();
           for (auto nextNode : adjList_[cur]) {
              int next = nextNode.second;
              if (parent[next] == -1 && res_[cur][next]) {
                   parent[next] = cur;
                   int new_flow = std::min(flow, res_[cur][next]);
                   if (next == t)
                       return new_flow;
                   q.push({next, new_flow});
              }
           }
       }
   }

private:
   std::vector<vi> res_;
};


class GraphDinic : public GraphMaxFlow
{
public:
   // ford_fulkerson + BFS/DFS
   // Returns maximum flow in graph
   int dinic(int s, int t)
   {
       // Corner case
       if (s == t)
           return -1;
 
       int total = 0;  // Initialize result
 
       // Augment the flow while there is path
       // from source to sink
       while (dinic_bfs(s, t) == true)
       {
           // store how many edges are visited
           // from V { 0 to V }
           int *start = new int[V_+1] {0};
 
           // while flow is not zero in graph from S to D
           while (int flow = dinic_sendFlow(s, INT_MAX, t, start))
 
               // Add path flow to overall flow
               total += flow;
       }
 
       // return maximum flow
       return total;
   }

   // Finds if more flow can be sent from s to t.
   // Also assigns levels to nodes.
   bool dinic_bfs(int s, int t)
   {
       for (int i = 0 ; i < V_ ; i++)
           level_[i] = -1;
 
       level_[s] = 0;  // Level of source vertex
 
       // Create a queue, enqueue source vertex
       // and mark source vertex as visited here
       // level[] array works as visited array also.
       std::queue< int > q;
       q.push(s);
 
       std::vector<DinicEdge>::iterator i ;
       while (!q.empty())
       {
           int u = q.front();
           q.pop();
           for (i = dinicAdj_[u].begin(); i != dinicAdj_[u].end(); i++)
           {
               DinicEdge &e = *i;
               if (level_[e.v] < 0  && e.flow < e.C)
               {
                   // Level of current vertex is,
                   // level of parent + 1
                   level_[e.v] = level_[u] + 1;
                   q.push(e.v);
               }
           }
       }
 
       // IF we can not reach to the sink we
       // return false else true
       return level_[t] < 0 ? false : true ;
   }

   // A DFS based function to send flow after BFS has
   // figured out that there is a possible flow and
   // constructed levels. This function called multiple
   // times for a single call of BFS.
   // flow : Current flow send by parent function call
   // start[] : To keep track of next edge to be explored.
   //           start[i] stores  count of edges explored
   //           from i.
   //  u : Current vertex
   //  t : Sink
   int dinic_sendFlow(int u, int flow, int t, int start[])
   {
       // Sink reached
       if (u == t)
           return flow;
 
       // Traverse all adjacent edges one -by - one.
       for (  ; start[u] < dinicAdj_[u].size(); start[u]++)
       {
           // Pick next edge from adjacency list of u
           DinicEdge &e = dinicAdj_[u][start[u]];
                                     
           if (level_[e.v] == level_[u]+1 && e.flow < e.C)
           {
               // find minimum flow from u to t
               int curr_flow = std::min(flow, e.C - e.flow);
 
               int temp_flow = dinic_sendFlow(e.v, curr_flow, t, start);
 
               // flow is greater than zero
               if (temp_flow > 0)
               {
                   // add flow  to current edge
                   e.flow += temp_flow;
 
                   // subtract flow from reverse edge
                   // of current edge
                   dinicAdj_[e.v][e.rev].flow -= temp_flow;
                   return temp_flow;
               }
           }
       }
 
       return 0;
   }

    // add edge to the graph
    void dinic_addEdge(int u, int v, int C)
    {
        // Forward edge : 0 flow and C capacity
        DinicEdge a{v, 0, C, dinicAdj_[v].size()};
 
        // Back edge : 0 flow and 0 capacity
        DinicEdge b{u, 0, 0, dinicAdj_[u].size()};
 
        dinicAdj_[u].push_back(a);
        dinicAdj_[v].push_back(b); // reverse edge
    }

private:
   // A structure to represent a edge between
   // two vertex
   struct DinicEdge
   {
       int v ;  // Vertex v (or "to" vertex)
                // of a directed edge u-v. "From"
                // vertex u can be obtained using
                // index in adjacent array.
 
       int flow ; // flow of data in edge
 
       int C;    // capacity
 
       int rev ; // To store index of reverse
                 // edge in adjacency list so that
                 // we can quickly find it.
   };

   vi level_; // stores level of a node
   std::vector<std::vector<DinicEdge>> dinicAdj_;
};


// Min Cost (Max) Flow
class GraphMcmf : public GraphMaxFlow
{
public:
   void init(int node_num)
   {
      node_num = node_num;
      G.assign(node_num, vi());
      vis.assign(node_num, 0);
      dis.assign(node_num, 0);
      father.assign(node_num, 0);
      change.assign(node_num, 0);
   }

    /* 
     * 存储边信息，一条有向边的正向弧和反向弧保存在一起，
     * 即ID为0和1的弧互为反向弧，ID为2和3的弧互为反向弧...
     * 弧i的反向弧为i ^ 1，其中 ^ 为二进制异或运算符
     * 
     * 无向边分解为两个有向边，即调用两次Add_Edge。
     */
    void Add_Edge(int from,int to,int cap,int cost)
    {  
        Edge edge();
        Edges.emplace_back(from, to, cap, 0, cost);   //正向弧
        Edges.emplace_back(to, from, 0, 0, -cost);    //反向弧
        int len = Edges.size();
        G[to].push_back(len-1);
        G[from].push_back(len-2);
    }

    //BellmanFord算法，最小费用最大流
    /*
     * SPFA(Shortest Path Faster Algorithm)
     * SPFA 在形式上和宽度优先搜索非常类似，
     * 不同的是宽度优先搜索中一个点出了队列就不可能重新进入队列，
     * 但是SPFA中一个点可能在出队列之后再次被放入队列，也就是一个点改进过其它的点之后，
     * 过了一段时间可能本身被改进，于是再次用来改进其它的点，这样反复迭代下去。
     * 设一个点用来作为迭代点对其它点进行改进的平均次数为k，
     * 有办法证明对于通常的情况，k在2左右。
     */
    bool BellmanFord(int s, int t, int& flow, int& cost)
    {
        int INF = 1e9;
        for(int i=0; i<node_num; i++)
            this->vis[i] = 0;
        for(int i=0; i<node_num; i++)
            this->dis[i] = INF;

        dis[s] = 0;
        vis[s] = 1;
        father[s] = -1;
        change[s] = INF;

        std::queue<int> q;
        q.push(s);
        while( !q.empty() )
        {
            int u = q.front();
            q.pop();
            vis[u] = 0;
            for(int i=0; i<G[u].size(); i++)
            {
                Edge& e = Edges[G[u][i]];
                if( e.cap>e.flow && dis[e.to]>dis[u]+e.cost )
                {
                    dis[e.to] = dis[u] + e.cost;
                    father[e.to] = G[u][i];
                    change[e.to] = std::min(change[u], e.cap-e.flow);
                    if(vis[e.to] == 0)
                    {
                        vis[e.to] = 1;
                        q.push(e.to);
                    }
                }
            }
        }

        if(dis[t] == INF)
            return false;
        flow += change[t];
        cost += dis[t]*change[t];

        //change[t]为当前路径的总流量
        OnePath temp_one_path;
        temp_one_path.Path_flow = change[t];
        for(int u = t; u!=s ; u = Edges[father[u]].from)
        {
            Edges[father[u]].flow += change[t];
            Edges[father[u]^1].flow -= change[t];
            //u即为路径上的点，此处是反向的
            if(u==t)
                continue;
            else
                temp_one_path.Path.push_back(u);
        }
        res_path.push_back(temp_one_path);
        return true;
    }


    /*
     * 需要从源点s运送至汇点t的全部物品。
     * 当问题为计算从s到t的最大流时，不需要maxflow；
     * 当问题为将全部物品maxflow从s运送至t时，需要maxflow。
     */
    int MinCostMaxFlow(int s, int t, int maxflow)
    {
        int flow = 0, cost = 0;
        while(BellmanFord(s, t, flow, cost));
        if(flow < maxflow)
            return -1;
        else
            return cost;
    }
private:
   struct Edge
   {
       int from, to, cap, flow, cost;
       Edge(int u, int v, int c, int f, int w)
       {
           from = u; to = v; cap = c; flow = f; cost = w;
       }
   };

   struct OnePath{
      int Path_flow;
      std::vector<int> Path;     // nodes on the path
   };

   int node_num;

   // 存储弧信息，
   // 一条无向边由两条有向边组成，
   // 每条有向边由正向弧（正向弧为这条边本身）和反向弧组成
   std::vector<Edge> Edges;
   // Adjacent list，G[i][j]表示结点i的第j条边在edges中的序号
   std::vector<vi> G;

   vi vis;       //标记矩阵，是否在队列中
   vi dis;       //Bellman-Ford
   vi father;    //上一条弧
   vi change;    //可改进量

   std::vector<OnePath> res_path;   //保存路径结果，以及对应路径上的总流量
};
