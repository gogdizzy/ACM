/*
@author gogdizzy
@date   2015-08-19

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1001

@solution
	2的因子个数比5多，只需要提取5的因子个数
*/

#include <stdio.h>

int main() {
	int  n, r = 0;
	scanf( "%d", &n );
	while( n ) {
		r += n /= 5;
	}
	printf( "%d\n", r );
	return 0;
}
