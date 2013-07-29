/**
*  http://51nod.com/onlineJudge/questionCode.html#!problemId=1024
*  矩阵中不重复的元素
*  思路：题目范围较小，可以硬算，只要设计好比较好的数据结构
*    能够重复的数据只能是这样的形式，a^x == b^y，则a^k = b 或 b^k = a
*    所以统计一下200以内的这样的数，在判断时，直接转为底数最小的形式。
*/

#include <stdint.h>
#include <stdio.h>

uint32_t appear[200][44];
uint32_t fact[200][2];

#define  SET_BIT( a, b ) do { int u = (a), v = (b); appear[u][v>>5] |= (1U<<(v&31)); } while(0)

int  count_bit1( uint32_t x ) {
	int  ans = 0;
	while( x ) {
		++ans;
		x &= (x-1);
	}
	return  ans;
}

int main() {
	int  m, n, a, b, x, y, k, ans = 0;
	scanf( "%d%d%d%d", &m, &n, &a, &b );

	for( x = 2; x < 200; ++x ) {
		if( fact[x][0] != 0 ) continue;
		for( y = x, k = 1; y < 200; y *= x, ++k ) {
			fact[y][0] = x;
			fact[y][1] = k;
		}
	}

	for( x = a; x < a + n; ++x ) {
		for( y = b; y < b + m; ++y ) {
			SET_BIT( fact[x][0], fact[x][1] * y );
		}
	}

	for( x = 2; x < a + n; ++x ) {
		for( y = 0; y < 44; ++y ) ans += count_bit1( appear[x][y] );
	}
	
	printf( "%d\n", ans );
	
	return 0;
}