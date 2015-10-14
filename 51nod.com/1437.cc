/*
@author gogdizzy
@date   2015-08-19

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1437

@solution
	这个题枚举要O( n^2 )肯定超时
	看到这种问题，有几个特性：
	1 是连续的一段区间，2 有区间最值的要求，3 枚举超时
	一般都是看看能不能用单调栈

	这个题首先计算出每个数据x作为最小值的控制范围，即找到它左右比它小的
	位置，它的控制范围就是中间这么大，设长度为L，从1到L的长度，都可以
	找到区间，使得该区间最小值为x

	对于示例数据
	10
	1 2 3 4 5 4 3 2 1 6

	可以找出
	1 [1, 10] // 就是1的控制范围长度是10，那么可以找到长度为1到10的子串，使得子串最小值为1
	2 [1, 7]
	3 [1, 5]
	4 [1, 3]
	5 [1, 1]
	6 [1, 1]

	所以对于长度为1，我们可以找到5和6，取6
	对于长度2和3，取4
	对于长度4和5，取3
	对于长度6和7，取2
	对于长度8~10，取1

	查找每个数的左右边界，就要用到单调栈了。	
*/

#include <stdio.h>

#define MAXN 200000
#define INF  2000000000

int a[MAXN+2];
int l[MAXN+2], r[MAXN+2];
int s[MAXN+2];
int sc;
int ans[MAXN+2];

inline
int max( int a, int b ) { return a > b ? a : b; }

int main() {

	int n, i;

	scanf( "%d", &n );
	for( i = 1; i <= n; ++i ) scanf( "%d", a + i );

	a[0] = INF, a[n+1] = -INF;
	sc = 0;
	s[sc++] = 0;
	for( i = 1; i <= n + 1; ++i ) {
		while( sc > 0 && a[ s[sc-1] ] > a[i] ) {
			r[ s[sc-1] ] = i;
			--sc;
		}
		s[sc++] = i;
	}
	
	a[0] = -INF, a[n+1] = INF;
	sc = 0;
	s[sc++] = n + 1;
	for( i = n; i >= 0; --i ) {
		while( sc > 0 && a[ s[sc-1] ] > a[i] ) {
			l[ s[sc-1] ] = i;
			--sc;
		}
		s[sc++] = i;
	}

	for( i = 1; i <= n; ++i ) {
		ans[ r[i] - l[i] - 1 ] = max( ans[ r[i] - l[i] - 1 ], a[i] );
	}

	for( i = n - 1; i >= 0; --i ) {
		ans[i] = max( ans[i+1], ans[i] );
	}

	for( i = 1; i <= n; ++i ) {
		printf( "%d ", ans[i] );
	}

	return 0;
}
