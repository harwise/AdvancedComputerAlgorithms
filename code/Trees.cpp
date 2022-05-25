/*
 * Trees
 *
 * 1. Connected undirected graph
 * 2. No cycles =
 *    (n vertices and n-1 edges) =
 *    only unique paths between any two vertices =
 *    (remove any edge and graph becomes disconnected)
 *
 * Diameter in a graph
 * -------------------
 *
 * The longest path of all the shortest paths between any two vertices.
 * For general graphs, apply Floyd-warshall's and a for loop. O(n^3)
 * For trees, it's simply the longest path in the tree. Brute force: O(n^2)
 *
 * Rooted Tree - digraph where edges directed away from root
 * Rooting the tree - pick a vertex to be the root. We do this because
 *                    rooted trees are much simpler to deal with.
 *
 * O(n) algorithm for finding diameter in a tree
 *
 * Algorithm 1. Rooting the tree. +
 *              Precompute the height of every vertex. (DFS) +
 *              Compute and compare the longest paths through roots of every subtree.
 *
 * Alogrithm 2. 1) Pick any node s; get the furthest node from s and call it t. (BFS)
 *              2) Get the furthest node from t and call it r. (BFS)
 *              3) r <-> t is the diameter.
 *
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
 *
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
 * 
 */

