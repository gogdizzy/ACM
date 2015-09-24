/*
@author gogdizzy
@date   2015-08-19

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1001

@solution
	每个点呈V型更新两侧所有的控制点，求得所有控制点能达到的最大值
	假设这些控制点都取最大值，看中间的点还能取多大
*/

#include <stdio.h>

#define MAXM 50

struct xt {
	int x, t;
	void set( int x0, int t0 ) { x = x0, t = t0; }
};

xt  p[MAXM];

inline
int abs( int a ) { return a < 0 ? -a : a; }
inline
int max( int a, int b ) { return a > b ? a : b; }
inline
int min( int a, int b ) { return a < b ? a : b; }

int main() {

	int  t, n, m, i, j;
	int  xi, ti, cnt;
	int  ans, tmp;

	for( scanf( "%d", &t ); t--; ) {
		scanf( "%d%d", &n, &m );

		ans = 0;
		p[0].set( 1, 0 );
		cnt = 1;
		for( i = 0; i < m; ++i ) {
			scanf( "%d%d", &xi, &ti );
			if( xi != 1 ) {
				p[cnt++].set( xi, ti );
			}
		}

		for( i = 0; i < cnt; ++i ) {
			for( j = 0; j < cnt; ++j ) {
				p[j].t = min( p[j].t, p[i].t + abs( p[i].x - p[j].x ) );
			}
		}

		for( i = 1; i < cnt; ++i ) {
			tmp = max( p[i].t, p[i-1].t );
			tmp = max( tmp, ( p[i].x - p[i-1].x + p[i].t + p[i-1].t ) / 2 );
			ans = max( ans, tmp );
		}

		if( p[cnt-1].x < n ) {
			tmp = n - p[cnt-1].x + p[cnt-1].t;
			ans = max( ans, tmp );
		}
		printf( "%d\n", ans );
	}

	return 0;
}
