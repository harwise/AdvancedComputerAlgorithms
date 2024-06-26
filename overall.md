问题可有由哪些变量描述
====================

* 变量的先后考虑顺序。
* 当解空间是单调的时候，考虑用二分查找找到解。（明显特征：求满足条件的最大或最小值。）


[直方图最大面积]
---------------
先考虑左右边界，不可避免 O(n^2)；但是如果先考虑高度，左右边界的取得就由优化方法。


Decrease and Conquer 减而治之
====================

* （自然的）最大，最小  => 单调队列（在已走过的数据中，只关心比最后一个值更大或更小的数。）
* 贪心选择下一个


[直方图最大面积]
---------------
左边的值中，比起当前值，只关心更小的那些，所以用**单调队列**来维护。


Greedy 贪心
======

* （预排序）最大，最小  => vector
* （维护的）最大，最小  => 堆（只关心最大或最小的那个数）


[Prim]
------


[Kruskal]
---------
选择 rank 最小的两个合并，**并查集**。


[Huffman Coding]
----------------
选择 rank 最小的两个合并，**并查集**


[Dijkstra]
----------

DFS，BFS 之外的 PFS（priority）。**优先队列/堆**


Divide and Conquer 分而治之
==================

* 分开的两部分不互相干涉，天然减少了重复计算。
* Merge的时候可以由子问题的结果定界。


[最短距离的点对]
---------------
由子问题的最优解定界。


动态规划
========

??????????????????????


二分图
=====

* 从节点来看，分两类。每一个节点只能有一条边。这条边或者说约束，会制约它再有其它边。
* 从边来看，它就是要求的解。

[象棋]
------


Graph 图
=====

* 节点和边的构建。题目中给出的 “边/关系” 可能更适合作为节点来建模。


欧拉回路
=====

* 所有边正好走一圈。

[大转盘]
--------

