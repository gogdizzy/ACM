/*
@author gogdizzy
@date   2015-08-19

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1001

@solution
	先排序，然后双指针从两侧向中间扫描
*/

#include <stdio.h>
#include <algorithm>

using namespace std;

#define MAXN 50000

int a[MAXN];

int main() {

	int  K, N, i, j, s, ans = 0;

	scanf( "%d%d", &K, &N );
	for( i = 0; i < N; ++i ) scanf( "%d", a + i );

	sort( a, a + N );

	for( i = 0, j = N - 1; i < j; ) {
		s = a[i] + a[j];
		if( s == K ) {
			printf( "%d %d\n", a[i], a[j] );
			++ans; ++i; --j; 
		}
		else if( s < K ) ++i;
		else --j;
	}

	if( !ans ) puts( "No Solution" );

	return 0;
}
