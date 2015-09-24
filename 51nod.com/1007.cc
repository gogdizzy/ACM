/*
@author gogdizzy
@date   2015-08-19

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1007

@solution
	dp[i]表示加和不超过i，能达到最接近i的和
	则对每一个数组值a[i]，更新一下[ a[i], sum/2 ]区间的dp值
*/

#include <stdio.h>

#define MAXN 100
#define MAXS 10000

short  a[MAXN];
short  dp[MAXS/2+1];

int main() {

	int  n, i, j, s = 0, s2;

	scanf( "%d", &n );
	for( i = 0; i < n; ++i ) {
		scanf( "%hd", a + i );
		s += a[i];
	}
	s2 = s / 2;

	for( i = 0; i < n; ++i ) {
		for( j = s2; j >= a[i]; --j )
			if( dp[j-a[i]] + a[i] > dp[j] ) dp[j] = dp[j-a[i]] + a[i];
	}
	printf( "%d\n", s - 2 * dp[s2] );
	return 0;
}
