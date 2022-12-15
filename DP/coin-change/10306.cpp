#include<bits/stdc++.h>
using namespace std ;
#define sizeArr(arr) sizeof arr/ sizeof *arr
#define INF 301

// 完全背包

struct coins
{
	int value;
	int tech;
}coin[41];
long long int dp[INF][INF] = {};

int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n, s;
		scanf("%d %d", &n, &s);
		for(int i=0 ; i<n ; i++)
			scanf("%d %d", &coin[i].value, &coin[i].tech);
		memset(dp, INF, sizeof dp);

		dp[0][0] = 0;
		for(int i=0 ; i<n ; i++)
		{
			int v = coin[i].value;
			int t = coin[i].tech;
			for(int x=v ; x*x+t*t<=s*s ; x++)
				for(int y=t ; x*x+y*y<=s*s ; y++)
					dp[x][y] = min(dp[x][y], dp[x-v][y-t]+1);		// input->output 方向会不会更好？因为input有很多无效元素。
		}

		long long int res = INF;
		for(int x=0 ; x<=s ; x++)
			for(int y=0 ; y<=s ; y++)
				if(x*x+y*y == s*s)
					res = min(res, dp[x][y]);

		if(res == INF)
			printf("not possible\n");
		else
			printf("%lld\n", res);
	}
	return 0 ;
}
