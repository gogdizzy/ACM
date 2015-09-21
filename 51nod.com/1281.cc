/*
@author gogdizzy
@date   2015-09-21

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1001

@solution
	解法1：先统计出每个山峰的位置，然后对[1,sqrt(N)+1]区间进行二分查找
		看最大的区间数是多少
		时间复杂度 log( sqrt(N) ) * sqrt(N) * log( N )
		空间复杂度 山峰点个数不超过数组一半
	解法2：每个点保存下一个山峰的位置，可以O(1)找到下一个山峰位置
		时间复杂度 log( sqrt(N) ) * sqrt(N)
		空间复杂度 和数组长度一样

*/

#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <algorithm>

#define  MAXN 50000

#define VER2
#ifdef VER1

uint16_t  peak[MAXN/2];
uint16_t  pcnt = 0;

int main() {


	int N, i, a = 0x7fffffff, b = a - 1, c;
	for( scanf( "%d", &N ), i = 0; i < N; ++i ) {
		scanf( "%d", &c );
		if( a < b && b > c ) peak[pcnt++] = i - 1;
		a = b; b = c;
	}

	if( pcnt < 2 ) {
		printf( "%hu\n", pcnt );
		return 0;
	}

	int l = 1, r = (int)sqrt( N ) + 1, mid, m;
	int last;
	uint16_t *pend = peak + pcnt, *pos;
	while( l <= r ) {
		m = mid = ( l + r ) / 2;
		last = peak[0];
		while( --m ) {
			pos = std::lower_bound( peak, pend, last + mid );
			if( pos == pend ) break;
			last = *pos;
		}
		if( m == 0 ) l = mid + 1;
		else r = mid - 1;
	}
	printf( "%d\n", r );
	return 0;
}

#endif

#ifdef VER2

uint16_t npeak[MAXN];
uint16_t pcnt = 0;

int main() {

	int  n, i, a = 0x7fffffff, b = a - 1, c;
	int  pre = 0;
	scanf( "%d", &n );
	for( i = 0; i < n; ++i ) {
		scanf( "%d", &c );
		if( a < b && b > c ) {
			++pcnt;
			while( pre < i ) npeak[pre++] = i - 1;
		}
		a = b; b = c;
	}

	if( pcnt < 2 ) {
		printf( "%hu\n", pcnt );
		return 0;
	}

	int  l = 1, r = (int)sqrt( n ) + 1, mid, m;
	int  last, pos;
	while( l <= r ) {
		m = mid = ( l + r ) / 2;
		last = npeak[0];
		while( --m ) {
			last = npeak[last + mid];
			if( last == 0 ) break;
		}
		if( m == 0 ) l = mid + 1;
		else r = mid - 1;
	}
	printf( "%d\n", r );
	return 0;
}

#endif
