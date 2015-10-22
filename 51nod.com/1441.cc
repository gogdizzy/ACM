/*
@author gogdizzy
@date   2015-10-21

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1441

@solution
	初始化所有数字的素因子个数
	然后阶乘相除就是因子个数相减

	时间复杂度分析：
	对于素因子2，需要执行 MAXN/2 + MAXN/4 + MAXN/8 + ...
	对于素因子3，需要执行 MAXN/3 + MAXN/9 + MAXN/27 + ...
	...
	因为 p + p^2 + p^3 + ... = ( 1 - p^n ) / ( 1 - p ) - 1 ≈ 1/(1-p) - 1  (当p<1时，n比较大时)
	又因为 p < 1/(1-p) - 1 < 2*p
	所以 MAXN * (1/2) < MAXN/2 + MAXN/4 + MAXN/8 + ... < MAXN * 2 * (1/2)
	同理 MAXN * (1/3) < MAXN/3 + MAXN/9 + MAXN/27 + ... < MAXN * 2 * (1/3)
	...
	对于所有素数p <= n，有 sigma(1/p) ≈ C * lnln(n)   (C是常数)
	所以时间复杂度是 O( MAXN * lnln(MAXN) )
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
