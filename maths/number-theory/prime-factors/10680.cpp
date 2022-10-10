#include <stdio.h>
#include <string.h>

int visit[1000001];
int prime[1000001];
int size[1000001];

int main()
{
   int prime_count = 0;
   for (int i = 2; i < 1000001; ++i) {
      if (!visit[i]) {
         prime[prime_count++] = i;
         for (int j = i + i; j < 1000001; j = j + i) {
            visit[j] = 1;
         }
      }
   }
   int n;
   while (~scanf("%d", &n) && n) {
      memset(size, 0, sizeof(size));
      for (int i = 0; i < prime_count && prime[i] <= n; ++i) {
         // 将前n个数的LCM因式分解
         long long now = prime[i] + 0LL, bound = n + 0LL;
         size[i] = 0;
         while (now <= bound) {
            now *= prime[i];
         }

         // 去掉5和2的公共个数即可（5不多于2）
         size[0] -= size[2];
         size[2] -= size[2];

         int ans = 1;
         for (int i = 0; i < prime_count && prime[i] <= n; ++i) {
            // 除2和5之外的其他素数尾数是1、3、5、7、9都是以4为周期的
            if (i != 0 && i != 2) {
               size[i] %= 4;
            }
            for (int j = size[i]; j >= 1; --j) {
               ans = (ans * prime[i]) % 10;
            }
         }

         printf("%d\n", ans);
      }
      return 0;
   }
