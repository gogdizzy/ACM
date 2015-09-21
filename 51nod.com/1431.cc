/*
@author gogdizzy
@date   2015-09-21
@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1431
@solution
	可以发现每个数字向前队伍头移动几个位置，就减去几，向后移动几个位置，就加上几
	因为数组头表示队伍尾部
	所以无论怎么移动，这个数字的值和它位置的和是相对不变的
	最后形成的合法序列就是从队尾到队头，数值非递减，位置增加，
	它们的和肯定是严格递增的，所以先对和进行排序，然后判断
	是否严格递增
*/

#include <stdio.h>
#include <algorithm>

using namespace std;

#define MAXN 200000

int sum[MAXN];

int main() {

	int n, i, x;

	scanf( "%d", &n );
	for( i = 0; i < n; ++i ) {
		scanf( "%d", &x );
		sum[i] = i + x;
	}

	sort( sum, sum + n );

	for( i = 1; i < n; ++i ) {
		if( sum[i] == sum[i - 1] ) {
			break;
		}
	}

	puts( i == n ? "Happy" : "Sad" );	

	return 0;
}
