#include <utility>
#include <functional>

typedef std::pair<int, int> ii;

/*
 * {x0, x1 = f(x0), x2 = f(x1), ......}
 * find the smallest mu and lambda such that
 * x_mu = x_(mu+lambda)
 * 
 * O(mu + lambda)
 */
ii floydCycleFinding(int x0, std::function<int(int)> f) {
   // 1st: hare's speed is 2x tortoise's. if x_i == x_(2i), i = k*lambda
   int tortoise = f(x0), hare = f(f(x0));
   while (tortoise != hare) { tortoise = f(tortoise); hare = f(f(hare)); }
   // 2nd: mu is the first one such that x_mu = x(mu + k*lambda)
   int mu = 0; hare = x0;
   while (tortoise != hare) { tortoise = f(tortoise); hare = f(hare); mu++; }
   // 3rd: lambda is the first one such that x_(mu + lambda) = x_mu
   int lambda = 1; tortoise = mu; hare = f(tortoise);
   while (tortoise != hare) { hare = f(hare); lambda++; }
   return ii(mu, lambda);
}
