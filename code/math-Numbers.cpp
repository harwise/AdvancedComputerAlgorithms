#include <cmath>
#include <bitset>
#include <vector>

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

private:
   uint64_t sieve_size_;
   std::bitset<10000010> bs_;    // 10^7 should be enough for most cases.
   std::vector<int> primes_;
};


// Caution: negative number is not supported!!!
// Greatest Common Divisor
unsigned gcd(unsigned a, unsigned b) {
   // O(logn) where n = max(a, b)
   return (b == 0 ? a : gcd(b, a % b));
}

// Least Common Multiple
unsigned lcm(unsigned a, unsigned b) {
   return a * (b / gcd(a, b));
}


/*
 * a.x + b.y = gcd
 * (b%a).x1 + a.y1 = gcd
 * (b - floor(b/a).a).x1 + a.y1  = gcd
 * b.x1 + a.(y1 - floor(b/a).x1) = gcd
 * 
 * x = y1 - floor(b/a).x1
 * y = x1
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

private:
   int x_;
   int y_;
   int d_;
};
