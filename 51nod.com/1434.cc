/*
@author gogdizzy
@date   2015-09-25

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1434

@solution
	题目要求 LCM(1..n) | LCM(n+1..m)
	我们知道 LCM(1..n) 可以看成是对每个数做质因子分解，对每个质因子，取
	出现过最大的幂相乘，进一步，我们可以知道
	LCM(1..n) = (2^p2) * (3^p3) * (5^p5) * ...
	其中 2^p2 <= n < 2^(p2+1)， 3^p3 <= n < 3^(p3+1) ...

	如果满足整除关系，那么 LCM(n+1..m) 所有质因子个数出现都不小于前面的
	出现次数，也就是对于 2^p2，必须能够找到 n + 1 <= c * (2^p2) <= m
	n + 1 <= c * (3^p3) <= m ...

	具体实现，先筛出所有小于等于n的质因子，对于每个质因子求lcm中的最大
	幂次，然后通过上面说的确认满足条件的m的最小值
*/

#include <stdio.h>
#include <math.h>

#define MAXN 1000000

int p[80000];  // about MAXN / ln( MAXN )
int pc = 0;
int c[80000];
int f[MAXN/32+1];

#define  TEST( n )  ( f[n>>5] & (1<<(n&31) ) )
#define  SET( n )  ( f[n>>5] |= (1<<(n&31)) )

inline
void  sieve( int x ) {
	int  rt = (int)sqrt( (double)x ) + 1;
	for( int i = 2; i <= x; ++i ) {
		if( !TEST(i) ) {
			p[pc++] = i;
			if( i < rt ) for( int j = i * i; j <= x; j += i ) SET( j );
		}
	}
	p[pc++] = MAXN + 1;  // just a barrier, not prime
}

int solve( int n ) {

	int i, j, tmp;
	int ans = n + 1;

	for( i = 0; p[i] <= n; ++i ) {
		tmp = p[i];
		// 为什么不用 tmp * p[i] <= n，因为数据范围导致int越界
		// 如果用64位整数，就可以把除法转乘法了
		while( tmp <= n / p[i] ) tmp *= p[i];
		tmp = ( n / tmp + 1 ) * tmp;
		if( tmp > ans ) ans = tmp;
	}
	return ans;
}

int main() {

	sieve( MAXN );

	int  t, i, n;

	scanf( "%d", &t );
	for( i = 0; i < t; ++i ) {
		scanf( "%d", &n );
		printf( "%d\n", solve( n ) );
	}

	return 0;
}
