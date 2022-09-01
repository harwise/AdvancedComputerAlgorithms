/*
注意到序列有一个特点，每个序列各个元素都不一样，那么我们只需要给第一个字符串里面的数字映射到一个上升的编码

比如 3 1 2 5 4 -> 1 2 3 4 5

然后用这个映射规则映射第二个字符串内的字符。

比如 1 2 3 4 10 -> 2 3 1 5 0 （没有在第一个序列中出现的数用0代替，反正不影响）

然后在第二个字符串使用最长上升子序列（O（nlogn）的算法，不就可以了吗。）
*/
#include<bits/stdc++.h> 
using namespace std;
const int INF=0x3f3f3f3f; 
const int maxn=250*250+5;
int num1[maxn],num2[maxn],dp[maxn]; 
int flag[maxn];
int main(){
	int t; cin>>t;
	for(int cnt=1;cnt<=t;cnt++){
		int n,p,q; cin>>n>>p>>q;
		p++; q++;
		int a;
		for(int i=1;i<=p;i++){ //编码 
			scanf("%d",&a);
			flag[a]=i;
			num1[i]=i;
		}
		for(int i=1;i<=q;i++) { //转化为最长上升子序列 orz。。。。。 
			scanf("%d",&a);
			if(flag[a]) num2[i]=flag[a];
			else num2[i]=0;
		}
		memset(dp,INF,sizeof(dp));
		dp[0]=0;
			if(dp[ind]<num2[i]) dp[++ind]=num2[i];
			else {
				int aim=lower_bound(dp+1,dp+1+ind,num2[i])-dp;
				dp[aim]=num2[i];
			}
		}
		cout<<"Case "<<cnt<<": "<<ind<<endl;
	}
	return 0;
}  
