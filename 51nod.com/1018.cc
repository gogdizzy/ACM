/*
@author gogdizzy
@date   2015-08-19

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1018

@solution
	直接调用库函数排序
*/

#include <stdio.h>
#include <algorithm>

int  a[50000];

int main() {
	int  n, i;
	for( scanf( "%d", &n ), i = 0; i < n; ++i ) scanf( "%d", a + i );
	std::sort( a, a + n );
	for( i = 0; i < n; ++i ) printf( "%d\n", a[i] );
	return 0;
}
