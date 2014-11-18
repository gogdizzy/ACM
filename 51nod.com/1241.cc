/*
  问题：
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1241
  解答：
	输入序列是从1~n
	寻找最长紧密递增的子序列，其余元素都需要重排
*/

#include <stdio.h>

#define MAXN 50000

unsigned short org_pos[MAXN + 1];

int main() {
	int  n, i, x, max_asc = 0, cur_pos, cur_asc;
	scanf( "%d", &n );
	for( i = 0; i < n; ++i ) {
		scanf( "%d", &x );
		org_pos[x] = i;
	}

	cur_asc = 1, cur_pos = org_pos[1];
	for( i = 2; i <= n; ++i ) {
		if( org_pos[i] > cur_pos ) {
			++cur_asc;
		}
		else {
			if( cur_asc > max_asc ) max_asc = cur_asc;
			cur_asc = 1;
		}
		cur_pos = org_pos[i];
	}
	if( cur_asc > max_asc ) max_asc = cur_asc;

	printf( "%d\n", n - max_asc );
	return 0;
}
