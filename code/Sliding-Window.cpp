#include <queue>

/*
 * Find the minimum of each possible sub-arrays with static size K.
 * {0, 5, 5, 3, 10, 0, 4} K = 3.
 * {0, 5, 5} - 0
 * {5, 5, 3} - 3
 * {5, 3, 10} - 3,
 * {3, 10, 0} - 0,
 * {10, 0, 4} - 0
 * 
 * The sliding window is sorted and modeled with a deque.
 */
void SlidingSortedWindow(int A[], int n, int K) {
   using ii = std::pair<int, int>;
   std::deque<ii> window;
   for (int i = 0; i < n; i++) {
      /*
       * 比当前数字大，而且更早出现的那些item，直接淘汰。
       * window仍然是sorted。
       */
      while (!window.empty() && window.back().first >= A[i])
         window.pop_back();
      window.push_back({A[i], i});

      /*
       * lazy deletion.
       * lazy机制避免了从deque中间删除一个item。
       */
      while (window.front().second <= i - K)
         window.pop_front();

      if (i + 1 >= K)
         printf("%d\n", window.front().first);
   }
}
