/**
*  http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1021
*  石子归并
*  思路：设dp[i][k]表示从第i堆开始，合并k堆所需要的最小代价。
*        初始状态：dp[i][0] = dp[i][1] = 0;
*        转移方程：dp[i][k] = min{ dp[i][j] + dp[i+j][k-j] + sum( a[i]...a[k] ) | j ∈[1,k-1] }
*        空间复杂度O(n^2)，时间复杂度O(n^3)
*/

#include <stdio.h>

#define  MAXN  101

int  sum[MAXN];
int  dp[MAXN][MAXN];

int main() {
	int  n, i, j, k, x, a, tmp;
	for( scanf( "%d", &n ), i = 1; i <= n; ++i ) {
		scanf( "%d", &x );
		sum[i] = sum[i-1] + x;
	}

	for( k = 2; k <= n; ++k ) {
		for( i = 0; i + k <= n; ++i ) {
			a = sum[i+k] - sum[i];
			dp[i][k] = 0x7fffffff;
			for( j = 1; j < k; ++j ) {
				tmp = dp[i][j] + dp[i+j][k-j] + a;
				if( tmp < dp[i][k] ) dp[i][k] = tmp;
			}
		}
	}

	printf( "%d\n", dp[0][n] );

	return 0;
}