#include <cmath>
#include <bitset>
#include <vector>
#include <tuple>
#include <algorithm>

int dec_num_digits(int a)
{
   return (int)std::floor(1 + std::log10(a));
}

int num_digits(int a, int base)
{
   return (int)std::floor(1 + (std::log10(a)/std::log10(base)));
}

namespace BitOp {
   void turn_on(int& S, int j) {
      S |= (1 << j);
   }
   bool is_on(int S, int j) {
      return 0 != (S & (1 << j));
   }
   void turn_off(int &S, int j) {
      S &= ~(1 << j);
   }
   void toggle(int &S, int j) {
      S ^= (1 << j);
   }
   int right_most_on_mask(int S) {
      return (S & (-S));
   }
   int right_n_bits_mask(int n) {
      return (1 << n) - 1;
   }
}

// Caution: negative number is not supported!!!
// Greatest Common Divisor
template <class T>
T gcd(T a, T b) {
   // O(logn) where n = max(a, b)
   return (b == 0 ? a : gcd(b, a % b));
}

// Least Common Multiple
template <class T>
T lcm(T a, T b) {
   return a * (b / gcd(a, b));
}


class Primes
{
public:
   std::vector<int> largePrimes() {
      return std::vector<int>{104729, 1299709, 15485863, 179424673, 2147483647};
   }

   // Only work for N <= primes_.back() ^ 2;
   /*
    * The number of primes less than or equal to N is pi(N).
    * pi(N) ~ O(N/(lnN-1))
    * ~ O(sqrt(N)/ln(sqrt(N)))
    * E.g. N = 10^6 -> pi(sqrt(N)) = 168.
    */
   std::vector<uint64_t> primeFactors(uint64_t N) {
      std::vector<uint64_t> factors;
      int PF_idx = 0;
      int PF = primes_[PF_idx];
      while (N != 1 && (PF * (uint64_t)PF <= N)) {
         while (N % PF == 0) {
            N /= PF;
            factors.push_back(PF);
         }
         PF = primes_[++PF_idx];
      }
      if (N != 1) {
         factors.push_back(N);
      }
      return factors;
   }

   // Pollard's rho Integer Factoring
   // break n into two non trivial factors.
   // we assume n is not a prime.
   /*
    * Let p one of the factor of n.
    * The key idea is that two integers x and y are congruent modulo p with
    * probability 0.5 after 1.177*sqrt(p) integers' have been randomly chosen.
    */
   uint64_t pollard_rho(uint64_t n) {
      int i = 0, k = 2;
      uint64_t x = 3, y = 3;  // random seed
      while (1) {
         i++;
         x = (mulmod(x, x, n) + n - 1) % n;  // generating function
         uint64_t d = gcd(y > x ? y - x : x - y, n);
         if (d != 1 && d != n)
            return d;
         if (i == k) {
            y = x;
            k *= 2;
         }
      }
   }
   template <class T>
   T mulmod(T a, T b, T c) {     // returns (a * b) % c, and minimize overflow
      T x = 0, y = a % c;
      while (b > 0) {
         if (b % 2 == 1)
            x = (x + y) % c;
         y = (y * 2) % c;
         b /= 2;
      }
      return x % c;
   }

   uint64_t numPF(uint64_t N) {
      uint64_t PF_idx = 0, PF = primes_[PF_idx], ans = 0;
      while (N != 1 && (PF * PF <= N)) {
         while (N % PF == 0) { N /= PF; ans++; }
         PF = primes_[++PF_idx];
      }
      if (N != 1) ans++;
      return ans;
   }

   uint64_t numDiv(uint64_t N) {
      uint64_t PF_idx = 0, PF = primes_[PF_idx], ans = 1;
      while (N != 1 && (PF * PF <= N)) {
         uint64_t power = 0;
         while (N % PF == 0) { N /= PF; power++; }
         ans *= (power + 1);
         PF = primes_[++PF_idx];
      }
      if (N != 1) ans *= 2;
      return ans;
   }

   uint64_t sumDiv(uint64_t N) {
      uint64_t PF_idx = 0, PF = primes_[PF_idx], ans = 1;
      while (N != 1 && (PF * PF <= N)) {
         uint64_t power = 0;
         while (N % PF == 0) { N /= PF; power++; }
         ans *= (uint64_t)(std::pow(PF, power + 1.0) - 1) / (PF - 1);
         PF = primes_[++PF_idx];
      }
      if (N != 1) ans *= ((uint64_t)std::pow(N, 2.0) - 1) / (N - 1);
   }

   // The number of integers < N and relatively prime to N.
   // The Euler's Phi: N * (1 - 1/2) * (1 - 1/3) * (1 - 1/5) ...
   uint64_t EulerPhi(uint64_t N) {
      uint64_t PF_idx = 0, PF = primes_[PF_idx], ans = 1;
      while (N != 1 && (PF * PF <= N)) {
         if (N % PF == 0) {ans -= ans / PF;}
         while (N % PF == 0) { N /= PF; }
         PF = primes_[++PF_idx];
      }
      if (N != 1) ans -= ans / N;
      return ans;
   }

   /*
    * N*(1/2 + 1/3 + 1/5 + 1/7 + ...)
    * ~ O(N * ln(lnN))
    */
   void sieve(uint64_t upperbound) {
      sieve_size_ = upperbound + 1;
      bs_.set();  // set all bits to 1
      bs_[0] = bs_[1] = 0;
      for (auto i = 2; i <= sieve_size_; i++) {
         if (bs_[i]) {
            // cross out multiples of i starting from i*i.
            for (auto j = i * i; j <= sieve_size_; j += i) {
               bs_[j] = 0;
            }
            primes_.push_back((int)i);
         }
      }
   }

   // Only work for N <= primes_.back() ^ 2;
   /*
    * The number of primes less than or equal to N is pi(N).
    * pi(N) ~ O(N/(lnN-1))
    * ~ O(sqrt(N)/ln(sqrt(N)))
    * E.g. N = 10^6 -> pi(sqrt(N)) = 168.
    */
   bool isPrime(uint64_t N) {
      if (N <= sieve_size_) {
         return bs_[N];
      }
      auto sqrtN = (int)std::sqrt(N);
      for (int i = 0; i < (int)primes_.size(); i++) {
         if (N % primes_[i] == 0) {
            return false;
         }
         if (primes_[i] > sqrtN) {
            break;
         }
      }
      return true;
   }


   // This function is called for all k trials. It returns
   // false if n is composite and returns true if n is
   // probably prime.
   // d is an odd number such that  d*2^r = n-1
   // for some r >= 1
   bool miillerTest(int d, int n)
   {
      // Pick a random number in [2..n-2]
      // Corner cases make sure that n > 4
      int a = 2 + rand() % (n - 4);

      // Compute a^d % n
      int x = power(a, d, n);

      if (x == 1 || x == n - 1)
         return true;

      // Keep squaring x while one of the following doesn't
      // happen
      // (i)   d does not reach n-1
      // (ii)  (x^2) % n is not 1
      // (iii) (x^2) % n is not n-1
      while (d != n - 1)
      {
         x = (x * x) % n;
         d *= 2;

         if (x == 1)      return false;
         if (x == n - 1)    return true;
      }

      // Return composite
      return false;
   }
   // Utility function to do modular exponentiation.
   // It returns (x^y) % p
   int power(int x, unsigned int y, int p)
   {
      int res = 1;      // Initialize result
      x = x % p;  // Update x if it is more than or
                  // equal to p
      while (y > 0)
      {
         // If y is odd, multiply x with result
         if (y & 1)
            res = (res * x) % p;

         // y must be even now
         y = y >> 1; // y = y/2
         x = (x * x) % p;
      }
      return res;
   }
   // It returns false if n is composite and returns true if n
   // is probably prime.  k is an input parameter that determines
   // accuracy level. Higher value of k indicates more accuracy.
   bool isPrime(int n, int k)
   {
      // Corner cases
      if (n <= 1 || n == 4)  return false;
      if (n <= 3) return true;

      // Find r such that n = 2^d * r + 1 for some r >= 1
      int d = n - 1;
      while (d % 2 == 0)
         d /= 2;

      // Iterate given number of 'k' times
      for (int i = 0; i < k; i++)
         if (!miillerTest(d, n))
            return false;

      return true;
   }


private:
   uint64_t sieve_size_;
   std::bitset<10000010> bs_;    // 10^7 should be enough for most cases.
   std::vector<int> primes_;
};


/*
 * a.x + b.y = gcd
 * (b%a).x1 + a.y1 = gcd
 * (b - floor(b/a).a).x1 + a.y1  = gcd
 * b.x1 + a.(y1 - floor(b/a).x1) = gcd
 * 
 * x = y1 - floor(b/a).x1
 * y = x1
 * 
 * Can be used to  solve Linear Diophantine Equation
 * 25x + 18y = 839.
 * Since we know that both x and y must be integers, this linear equation is called the Linear
 * Diophantine Equation. We can solve Linear Diophantine Equation with two variables even
 * if we only have one equation!
 */

class ExtendedEuclid
{
public:
   /* solve ax + by = gcd(a, b)
    * x_, y_ is one slution. Other solutions are:
    * a(x_ + n * b/gcd) + b(y_ - n * a/gcd) = gcd(a, b)
    */
   void Solve(int a, int b) {
      if (b == 0) { x_ = 1; y_ = 0; d_ = a; return; }
      Solve(b, a % b);
      int x1 = y_;
      int y1 = x_ - (a / b) * y_;
      x_ = x1;
      y_ = y1;
   }

   /* solve ax + by = gcd(a, b) */
   static int SolveIterative(int a, int b, int &x, int &y) {
      /*
       * invariants:
       * a*x + b*y = a1
       * a*x1 + b*y1 = b1
       * 
       * a*1 + b*0 = a1
       * a*0 + b*1 = b1
       */
      x = 1, y = 0;
      int x1 = 0, y1 = 1, a1 = a, b1 = b;

      while (b1) {
         /*
          *   (a*x + b*y = a1)
          * - (a*x1 + b*y1 = b1)*q
          * ----------------------
          * = a*(x-q*x1) + b*(y-q*y1) = a1 - q*b1
          * 
          * Notice that (a1 - q*b1 = a1 % b1)
          */
         int q = a1 / b1;
         std::tie(x, x1) = std::make_tuple(x1, x - q * x1);
         std::tie(y, y1) = std::make_tuple(y1, y - q * y1);
         std::tie(a1, b1) = std::make_tuple(b1, a1 - q * b1);
      }

      /*
       * Finally, b1 = 0, a1 = gcd(a,b).
       * i.e. a*x + b*y = a1 = gcd(a,b).
       */
      return a1;
   }

private:
   int x_;
   int y_;
   int d_;
};


/*
 * Chinese Remainder Theorem
 * 
 * x =  ( ∑ (rem[i]*pp[i]*inv[i]) ) % prod
 * Where 0 <= i <= n-1

 * rem[i] is given array of remainders

 * prod is product of all given numbers
 * prod = num[0] * num[1] * ... * num[k-1]

 * pp[i] is product of all divided by num[i]
 * pp[i] = prod / num[i]

 * inv[i] = Modular Multiplicative Inverse of 
 *          pp[i] with respect to num[i]
 */


/*
 * Josephus Problem
 * 
 * n: the size of the circle. Members are indexed 0, 1, 2, ..., n-1.
 * k: execute the k-th person.
 * F(n, k) denotes the position of the survivor for a circle of size n and with
 *         k skipping rule.
 * 
 * F(n, k) = (F(n-1, k) + k) % n
 * 
 * For the k = 2 case,
 * if n = 1xxxxx in binary representation, the answer is xxxxx1.
 */
