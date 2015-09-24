/*
@author gogdizzy
@date   2015-08-19

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1013

@solution
	根据等幂求和公式，最后结果要除以2，为了避免大数运算，对质数取模的除法
	相当于乘以2对P的逆元
*/

#include <stdio.h>

#define  ULL   unsigned long long
#define  P     1000000007U
#define  Inv2  ( ( P + 1 ) / 2 )

int main() {
	unsigned int  n;
	ULL  mod = 1, tmp = 3ULL;
	scanf( "%u", &n ); ++n;
	while( n ) {
		if( n & 1 ) mod = mod * tmp % P;
		tmp = tmp * tmp % P;
		n >>= 1;
	}
	
	printf( "%llu\n", ( mod + P - 1 ) * Inv2 % P );
	return 0;
}
