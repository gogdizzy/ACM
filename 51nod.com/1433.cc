/*
@author gogdizzy
@date   2015-09-21
@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1433
@solution
	能被90整除，就要分别被9和10整除，被9整除就是所有数字和加起来可以整除9
	被10整除就是末位是0
*/

#include <stdio.h>

int main() {
	
	int n, i, x;
	int c0 = 0, c5 = 0;
	
	scanf( "%d", &n );
	for( i = 0; i < n; ++i ) {
		scanf( "%d", &x );
		++( x == 0 ? c0 : c5 );
	}

	if( c0 == 0 ) puts( "-1" );
	else if( c5 < 9 ) puts( "0" );
	else {
		c5 = c5 / 9 * 9;
		for( i = 0; i < c5; ++i ) putchar( '5' );
		for( i = 0; i < c0; ++i ) putchar( '0' );
		putchar( '\n' );
	}
	
	return 0;
}
