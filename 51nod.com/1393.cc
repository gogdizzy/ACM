/*
@author gogdizzy
@date   2015-08-19

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1393

@solution
	遇到0减一，遇到1加一
	记录前缀和，相等的前缀和，它们之间的0和1个数相等
*/

#include <stdio.h>

#define MAXN 1000000

int  beg0[MAXN*2+1], *beg = beg0 + MAXN;

int main() {
	int  c, i = 1, sum = 0, ans = 0;
	
	beg[0] = 1;
	while( (c = getchar()) != EOF ) {
		++i;
		sum += (c == '0' ? -1 : 1 );
		if( beg[sum] == 0 ) beg[sum] = i;
		if( ans < i - beg[sum] ) ans = i - beg[sum];
	}
	
	printf( "%d\n", ans );
	return 0;
}
