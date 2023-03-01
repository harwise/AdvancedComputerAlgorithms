/*
 * Heap
 * Segment Tree
 * Fenwick Tree
 */

/*
 * Heap
 *
 * A binary heap is always a COMPLETE binary tree, it can be stored compactly.
 *
 * The root is placed at index 1, in order to simplify arithmetic.
 * Valid indices are 1 through n.
 * 
 * children: 2*i, 2*i+1
 * parent: floor(i/2)
 * 
 * example: 6 elements. index [1, 6].
 *          {1, 3, 5, 7, 8, 9}
 * 
 *                     1(i=1)
 *                    /       \
 *                  5(i=2)    3(i=3)
 *                 /   \      /
 *                7(4) 9(5)  8(6)
 */

/*
 * Segment Tree (including LiChao Tree)
 *
 * The root is placed at index 1, in order to simplify arithmetic.
 * Valid indices are 1 through n.
 *
 * Not a complete tree.
 * Leaf nodes are elements; internal nodes are segments.
 * The count of nodes is at most 2 * 2^(floor(log2(N))+1) < 4 * N.
 * 
 * example: 6 elements. index [1, 24].
 *          (1, 3, 5, 7, 8, 9)
 * 
 * 
 *                                           segment1-6(i=1)
 *                                         /                 \
 *                                      seg1-3(i=2)         seg4-6(i=3)
 *                                      /       \            /          \
 *                               seg1-2(4)      5(5)  seg4-5(6)         9(7)
 *                                 /     \              /     \
 *                             1(8)       3(9)        7(12)   8(13)
 */

/*
 * Fenwick Tree
 *
 * example: 6 elements. index [1, 6].
 * 
 * 1,    1,    1,    1,    1,    1
 * 0001, 0010, 0011, 0100, 0101, 0110
 * [1]        [3]         [5]
 * [1----2]               [5-----6]
 * [1----------------4]
 *
 */
