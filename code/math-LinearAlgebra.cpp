#include <cmath>
#include <vector>


class LinearEquations
{
public:
   void GuassianElimination(int N) {
      int i, j, k, l;
      double t;
      for (j = 0; j < N - 1; j++) {
         l = j;
         for (i = j + 1; i < N; i++)   // which row has the larget column value
            if (fabs(mat_[i][j]) > fabs(mat_[l][j]))
               l = i;
         // swap the pivot row, reason: to minimize floating point error
         for (k = j; k <= N; k++)
            std::swap(mat_[j][k], mat_[l][k]);
         for (i = j + 1; i < N; i++)
            for (k = N; k >= j; k--)
               mat_[i][k] -= mat_[j][k] * mat_[i][j] / mat_[j][j];
      }

      for (j = N - 1; j >= 0; j--) {
         for (t = 0.0, k = j + 1; k < N; k++)
            t += mat_[j][k] * vec_[k];
         vec_[j] = (mat_[j][N] - t) / mat_[j][j];
      }
   }

private:
   static constexpr int MAX_N_ = 100;
   double mat_[MAX_N_][MAX_N_ + 1];    // the last columen is the b in M*x = b.
   double vec_[MAX_N_];                // the answer x.
};
