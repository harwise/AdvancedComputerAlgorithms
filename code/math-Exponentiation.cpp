#include <utility>
#include <functional>

// O(log(p))
int fastExp(int base, int p) {
   if (p == 0) return 1;
   if (p == 1) return base;

   int res = fastExp(base, p / 2);
   res *= res;
   if (p % 2 == 1) res *= base;
   return res;
}


class Matrix {
public:
   static Matrix matMul(Matrix a, Matrix b) {
      Matrix ans;
      for (int i = 0; i < MAX_N; i++)
         for (int j = 0; j < MAX_N; j++) {
            ans.mat_[i][j] = 0;
            for (int k = 0; k < MAX_N; k++)
               ans.mat_[i][j] += a.mat_[i][k] * b.mat_[k][j];
         }
      return ans;
   }

   // O(n^3 * log(p))
   static Matrix matPow(Matrix base, int p) {
      Matrix ans;
      for (int i = 0; i < MAX_N; i++)
         for (int j = 0; j < MAX_N; j++)
            ans.mat_[i][j] = (i == j);
      // iterative version
      while (p) {
         if (p & 1) ans = matMul(ans, base);
         base = matMul(base, base);
         p >>= 1;
      }
      return ans;
   }

private:
   constexpr static int MAX_N = 10;
   int mat_[MAX_N][MAX_N];
};
