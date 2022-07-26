#include <cstdio>
#include <cstring>
int g[110][110];
int visit[110][110];
int book[110];
int n;
void dfs(int x){
	book[x] = 1;
	for(int i = 0; i < n; i++){
		if(book[i] == 0 && g[x][i] == 1)
			dfs(i);
	}
}
void prow(){
	putchar('+');
	for(int i = 0; i < n * 2 - 1; i++)
		putchar('-');
	puts("+");
}
int main(){
	// freopen("i.txt", "r", stdin);
	// freopen("o.txt", "w", stdout);
	int t, c = 1; scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				scanf("%d", &g[i][j]);
		for(int i = 0; i < n; i++){
			memset(book, 0, sizeof(book));
			book[i] = -1;//暂时去除该点
			dfs(0);
			book[i] = 0;
			for(int j = 0; j < n; j++)
				visit[i][j] = book[j];
		}
		visit[0][0] = 1;//记得将特殊情况补上
		for(int i = 1; i < n; i++)
			for(int j = 0; j < n; j++)
				visit[i][j] ^= visit[0][j];//异或
		
		printf("Case %d:\n", c++);
		for(int i = 0; i < n; i++){
			prow();
			putchar('|');
			for(int j = 0; j < n; j++)
				printf("%c|", visit[i][j] == 1 ? 'Y' : 'N');
			puts("");
		}
		prow();
	}
}