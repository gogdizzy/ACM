/*
@author gogdizzy
@date   2015-08-19

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1014

@solution
	直接尝试枚举
	设x是第一个满足条件的数，y是第二个，则 ( y^2 - x^2 ) = k * p
	即 ( y + x ) * ( y - x ) = k * p
	因为x和y不相等，都在[0,p]区间，所以y - x < p，0 < y + x < 2p，
	所以y + x = p
	也就是说，要么没有答案，要么找到x，直接输出x和p-x即可
*/

#include <stdio.h>

int main() {
	int  a, p, x, z = 1;

	scanf( "%d%d", &p, &a );
	for( x = 1; x <= p; ++x )
		if( (long long)x * x % p == a ) { z = 0; break; }

	if( z ) puts( "No Solution" );
	else printf( "%d %d\n", x, p - x );

	return 0;
}
