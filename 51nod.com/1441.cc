/*
@author gogdizzy
@date   2015-10-21

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1441

@solution
	初始化所有数字的素因子个数
	然后阶乘相除就是因子个数相减
*/


#include <stdio.h>

#define MAXN 5000000

int sum[MAXN+1];

void init() {

	for( int i = 2; i <= MAXN; ++i ) {
		if( sum[i] == 0 ) {
			long long j, k;
			for( j = i; j <= MAXN; j *= i ) {
				for( k = j; k <= MAXN; k += j ) {
					++sum[k];
				}
			}
		}
		sum[i] += sum[i-1];
	}

}

int main() {

	int t, a, b;

	init();

	scanf( "%d", &t );
	while( t-- ) {
		scanf( "%d%d", &a, &b );
		printf( "%d\n", sum[a] - sum[b] );
	}

	return 0;
}
