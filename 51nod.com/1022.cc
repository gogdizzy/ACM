/**
*  http://51nod.com/onlineJudge/questionCode.html#!problemId=1022
*  石子归并 V2
*  思路：设dp[i][k]表示从第i堆开始，合并k堆所需要的最小代价。注意本题是环形石子堆。
*    初始状态：dp[i][0] = dp[i][1] = 0;
*    转移方程：dp[i][k] = min{ dp[i][j] + dp[(i+j)%n][k-j] + sum( a[i]...a[k] ) | j ∈[1,k-1] }
*    数据量是10^3，用O(n^3)的时间复杂度已经不能满足时间限制了，需要用四边形不等式加速，使得
*    时间复杂度优化为O(n^2)
*    代码中用split数组记录上一轮dp的最优分割点，本轮只需要在相邻的分割点之间找最优值就行了。
*/

#include <stdio.h>

#define  LL  int
#define  MAXN  1001

LL  sum[MAXN];
LL  dp[MAXN][MAXN];
short  split[MAXN][MAXN];

int main() {
	int  n, i, j, k, x;
	LL   a, tmp;
	for( scanf( "%d", &n ), i = 1; i <= n; ++i ) {
		scanf( "%d", &x );
		sum[i] = sum[i-1] + x;
	}

	for( i = 0; i < n - 1; ++i ) {
		dp[i][2] = sum[i+2] - sum[i];
		split[i][2] = i + 1;
	}
	dp[n-1][2] = sum[n] - sum[n-1] + sum[1];
	split[n-1][2] = 0;

	for( k = 3; k <= n; ++k ) {
		for( i = 0; i < n; ++i ) {
			if( i + k <= n ) a = sum[i+k] - sum[i];
			else  a = sum[n] - sum[i] + sum[i+k-n];
			dp[i][k] = 0x7fffffff;
			int  beg = split[i][k-1], end = split[(i+1)%n][k-1];
			if( beg < i ) beg += n;
			if( end < beg ) end += n;
			for( j = beg; j <= end; ++j ) {
				tmp = dp[i][j-i] + dp[j%n][i+k-j] + a;
				if( tmp < dp[i][k] ) {
					dp[i][k] = tmp;
					split[i][k] = j%n;
				}
			}
		}
	}
	
	for( tmp = 0x7fffffff, i = 0; i < n; ++i ) {
		if( dp[i][n] < tmp ) tmp = dp[i][n];
	}
	printf( "%d\n", tmp );
	
	return 0;
}