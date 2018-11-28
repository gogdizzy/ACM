/**
 * http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1627
 * 瞬间移动
 * 思路：
 **/

#include <stdio.h>

#define ULL unsigned long long
#define P 1000000007

ULL comb( int n, int m ) {
	if( m > n / 2 ) m = n - m;
	ULL ans = 1;
	for( int i = n, j = 1; j <= m; ++j, --i ) {
		ans = ans * i / j % P;
	}
	return ans;
}

int main() {
	int m, n;
	scanf( "%d%d", &m, &n );
	printf( "%llu\n", comb( m + n - 4, m - 2 ) );
	return 0;
}

