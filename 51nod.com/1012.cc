/*
@author gogdizzy
@date   2015-08-19

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1012

@solution
	先求gcd，再求lcm
*/


#include <stdio.h>

template <typename T>
T gcd( T a, T b ) {
	return b == 0 ? a : gcd( b, a % b );
}

template <typename T>
T lcm( T a, T b ) {
	return a / gcd( a, b ) * b;
}

int main() {

	int a, b;

	scanf( "%d%d", &a, &b );
	printf( "%d\n", lcm( a, b ) );

	return 0;
}
