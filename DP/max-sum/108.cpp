/*
题目大意
题目给出 n*n 的矩阵，找每个数字之和最大的子矩阵，并输出最大和。
解题思路
先计算前i列的前缀和，这样用相减就能得到任意一段的和。核心思想就是使得二维转化为一维，利用连续子序列最大和解决。
*/

#include<stdio.h>
#include<string.h>
int a[200][200];
int main()
{
    int n,i,j,k,sum,maxx;
    while(~scanf("%d",&n))
    {
        maxx=-9999999;
        memset(a,0,sizeof(a));
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
             {
            scanf("%d",&a[i][j]);
            a[i][j]+=a[i-1][j];            //每一个a[i][j]表示（i=0）~（i=i）所有a[i][j]的和
             }
        for(i=0;i<n;i++)                  
            for(j=i+1;j<n;j++)
            {
                sum=0;
                for(k=0;k<n;k++)
                {
                    if(sum<0)
                        sum=0;
                    else sum+=a[j][k]-a[i-1][k];//理解为什么减a[i-1][k]很重要
                    if(sum>maxx&&sum!=0)
                       maxx=sum;              //记录最大的结果
                }
            }

        printf("%d\n",maxx);
    }
    return 0;
}
