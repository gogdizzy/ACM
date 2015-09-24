/*
@author gogdizzy
@date   2015-08-19

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1015

@solution
	直接先算出来，查表
*/

#include <stdio.h>

int main() {
	int  m, i, a[] = { 153, 370, 371, 407, 1634 };
	scanf( "%d", &m );
	for( i = 0; ; ++i ) if( a[i] >= m ) { printf( "%d\n", a[i] ); break; }
	return 0;
}
