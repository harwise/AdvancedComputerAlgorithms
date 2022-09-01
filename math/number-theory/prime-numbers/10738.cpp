#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef long long ll;
ll m[1000002];
ll M[1000002];
ll mi[1000002];
ll modsieve(ll n)
{
   ll i, j;
   for (i = 2; i <= 1000000; i++)
   {
      if (mi[i] == 0)
      {
         for (j = i; j <= 1000000; j = j + i)
         {
            m[j] = m[j] * i;
            mi[j]++;
         }
      }
   }
   for (i = 1; i <= 1000000; i++)
   {
      if (m[i] != i)
         m[i] = 0;
      else if (mi[i] % 2 == 0)
         m[i] = 1;
      else
         m[i] = -1;
   }
}
int main()
{
   m[1] = 1;
   ll i;
   for (i = 1; i <= 1000000; i++)
      m[i] = 1;
   memset(M, 0, sizeof(M));
   memset(mi, 0, sizeof(mi));
   modsieve(1000000);
   for (i = 1; i <= 1000000; i++)
      M[i] = M[i - 1] + m[i];
   ll n;
   while (scanf("%lld", &n) && n != 0)
   {
      printf("%8lld%8lld%8lld\n", n, m[n], M[n]);
   }
   return 0;
}
