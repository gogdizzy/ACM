/*
@author gogdizzy
@date   2015-08-19

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1081

@solution
	求前缀和
*/

#include <stdio.h>

#define MAXN 50000
long long  s[MAXN+2];

int main() {

	int n, i, q, a, b;

	scanf( "%d", &n ); ++n;
	for( i = 2; i <= n; ++i ) {
		scanf( "%d", &a );
		s[i] = s[i-1] + a;
	}

	scanf( "%d", &q );
	while( q-- ) {
	scanf( "%d%d", &a, &b );
		printf( "%lld\n", s[a+b] - s[a] );
	}
	return 0;
}
