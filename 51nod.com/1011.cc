/*
@author gogdizzy
@date   2015-08-19

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1011

@solution
	欧几里得辗转相除
*/

#include <stdio.h>

template <typename T>
T gcd( T a, T b ) {
	return b == 0 ? a : gcd( b, a % b );
}

int main() {

	int a, b;

	scanf( "%d%d", &a, &b );
	printf( "%d\n", gcd( a, b ) );

	return 0;
}
