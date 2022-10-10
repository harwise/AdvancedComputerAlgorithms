#include <string>
#include <map>


/*
 * UVA 10181
 */

static int DR[] = { 0,-1, 0, 1}; // E,N,W,S
static int DC[] = { 1, 0,-1, 0}; // R,U,L,D
static const char ANS[] = "RULD";
constexpr int INF = 1e9;

class IDAStar {
public:
   void ReadInput() {
      for (int i = 0; i < ROW_SIZE; i++) {
         for (int j = 0; j < ROW_SIZE; j++) {
            scanf("%d", &p_[i * ROW_SIZE + j]);
            if (p_[i * ROW_SIZE + j] == 0) {
               p_[i * ROW_SIZE + j] = X;   // change to X (15)
            } else
               p_[i * ROW_SIZE + j]--;     // use 0-based indexing
         }
      }
   }

   std::string Solve() {
      int blank = 0;
      for (int i = 0; i < PUZZLE; i++) {
         if (p_[i] == X) {
               blank = i;
         }
      }

      /*
       * 当移动空格时可以发现，左右移动，是不改变这15个数字对应的序列的。
       * 而上下移动，会将4个数字的位置进行改变，这样会导致逆序数的奇偶性改变（+-3或+-1）。
       * 同时我们还要让空格移动到右下角的位置。
       * 
       * 15个数字的逆序数加上空格移动到右下角的需要的行数的和 与
       * 目标状态的逆序数的奇偶性相同。
       * 因为最终的状态的逆序数是偶数，所以给出的局面也应该是偶数。
       */
      int sum = 0;
      for (int i = 0; i < PUZZLE; i++) {
         for (int j = 0; j < i; j++) {
            if (p_[i] != X && p_[j] != X && p_[j] > p_[i])
               sum++;
         }
      }
      sum += blank / ROW_SIZE;

      int ans = 0;
      if (sum % 2 != 0 && ((ans = IDA_Star()) != -1))
         output(ans), printf("\n");
      else
         printf("This puzzle is not solvable.\n");
   }

   int IDA_Star() {
      /*
       * lim_是（估计）需要多少步才能到达目标；这个估计值必须要小于真实值。
       * 一开始是通过 Manhattan distance 来估计需要多少步；
       * 在搜索解空间的过程中，不断调整lim_的值；(A*: g(s) + h(s))
       * 当到达目标后，lim_就是精确值了。
       * 
       * In order for a heuristic to be admissible to the search problem,
       * the estimated cost must always be lower than or equal to the
       * actual cost of reaching the goal state. 
       */
      lim_ = h1();
      while (true) {
         nlim_ = INF;
         pred_.clear();
         vis_.clear();
         if (DFS(0, h1()))
            return lim_;
         if (nlim_ == INF)
            return -1;
         // Interative Deepening!
         lim_ = nlim_; // nlim > lim
         if (lim_ > 45) // pruning condition in the problem
            return -1;
      }
   }

   // A*: g(s) + h(s)
   bool DFS(int g, int h) {
      if (g + h > lim_) {
         /*
          * 取最小值。即从当前层往前扩展的时候，尽量少扩展。
          */
         nlim_ = std::min(nlim_, g + h);
         return false;
      }

      if (goal()) {
         return true;
      }

      uint64_t state = 0;
      for (int i = 0; i < PUZZLE; i++) { // transform 16 numbers into 64 bits, exactly into 64 bits
         state <<= 4; // move left 4 bits
         state += p_[i]; // add this digit (max 15 or 1111)
      }
      if (vis_.count(state) && vis_[state] <= g) {
         // not pure backtracking... this is to prevent cycling
         return false;
      }
      vis_[state] = g;  // mark this as visited;

      int i, j, d, new_i, new_j;
      for (i = 0; i < PUZZLE; i++)
         if (p_[i] == X)
            break;
      j = i % 4;
      i /= 4;

      for (d = 0; d < 4; d++) {
         new_i = i + DR[d];
         new_j = j + DC[d];
         if (valid(new_i, new_j)) {
            int dh = h2(i, j, new_i, new_j);
            swap(i, j, new_i, new_j);
            // 记录第 g + 1 步走的是哪个方向
            pred_[g + 1] = d;
            if (DFS(g + 1, h + dh))
               return true;
            swap(i, j, new_i, new_j);  // restore
         }
      }
      return false;
   }

private:
   void output(int d) {
      if (d == 0)
         return;
      output(d - 1);
      printf("%c", ANS[pred_[d]]);
   }

   inline int h1() { // heuristic: sum of Manhattan distances (compute all)
      int ans = 0;
      for (int i = 0; i < PUZZLE; i++) {
         int tgt_i = p_[i] / 4, tgt_j = p_[i] % 4;
         if (p_[i] != X)
            ans += abs(i / 4 - tgt_i) + abs(i % 4 - tgt_j); // Manhattan distance
      }
      return ans;
   }

   // 把 X 从(i1, j1)移到(i2, j2)
   inline int h2(int i1, int j1, int i2, int j2) { // heuristic: sum of manhattan distances (compute delta)
      int tgt_i = p_[i2 * 4 + j2] / 4, tgt_j = p_[i2 * 4 + j2] % 4;
      return -(abs(i2 - tgt_i) + abs(j2 - tgt_j)) + (abs(i1 - tgt_i) + abs(j1 - tgt_j));
   }

   inline bool goal() {
      for (int i = 0; i < PUZZLE; i++)
         if (p_[i] != X && p_[i] != i)
            return false;
      return true;
   }

   inline bool valid(int r, int c) {
      return 0 <= r && r < 4 && 0 <= c && c < 4;
   }

   inline void swap(int i, int j, int new_i, int new_j) {
      std::swap(p_[i * 4 + j], p_[new_i * 4 + new_j]);
   }

private:
   static const int ROW_SIZE = 4; // ROW_SIZE is a matrix of 4 x 4
   static const int PUZZLE = ROW_SIZE*ROW_SIZE;
   static const int X = 15;
   int p_[PUZZLE];
   std::map<int, int> pred_;
   std::map<unsigned long long, int> vis_;      // visited
   int lim_;
   int nlim_;
};

