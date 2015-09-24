/*
@author gogdizzy
@date   2015-08-19

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1010

@solution
	看数据范围10^18，最多有61个2因子，有39个3因子，有27个5因子
	所以先将所有的可能数字都求出来，排序，然后二分查找。
*/

#include <stdio.h>
#include <algorithm>

#define  ULL  unsigned long long
#define  MAXN  1500000000000000000ULL
#define  P2  61
#define  P3  39
#define  P5  27
ULL  tbl[P2*P3*P5+5];
int  cnt = 0;

int main() {
	int  t, i, j, k;
	ULL  x, m1, m2, m3;
	for( i = 0, m1 = 1; m1 < MAXN && i < P2; ++i, m1 *= 2 ) {
		for( j = 0, m2 = m1; m2 < MAXN && j < P3; ++j, m2 *= 3 ) {
			for( k = 0, m3 = m2; m3 < MAXN && k < P5; ++k, m3 *= 5 ) {
				tbl[cnt++] = m3;
			}
		}
	}
	std::sort( tbl, tbl + cnt );

	scanf( "%d", &t );
	while( t-- ) {
		scanf( "%llu", &x );
		printf( "%llu\n", *std::lower_bound( tbl + 1, tbl + cnt, x ) );
	}
	return 0;
}
