/**
*  http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1007
*  正整数分组
*  思路：dp[i]表示加和不超过i，能达到最接近i的和
*	则对每一个数组值a[i]，更新一下[ a[i], sum/2 ]区间的dp值
*/

#include <cstdio>

int main() {
	int  n, i, j, s = 0, s0;
	short  a[100];
	short  dp[5001] = { 0 };
	scanf( "%d", &n );
	for( i = 0; i < n; ++i ) { scanf( "%hd", &a[i] ); s += a[i]; }
	s0 = s;
	s /= 2;
	for( i = 0; i < n; ++i ) {
		for( j = s; j >= a[i]; --j )
			if( dp[j-a[i]] + a[i] > dp[j] ) dp[j] = dp[j-a[i]] + a[i];
	}
	printf( "%d\n", s0 - 2 * dp[s] );
	return 0;
}