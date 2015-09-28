/*
@author gogdizzy
@date   2015-08-19

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1020

@solution
	参考答案：http://user.qzone.qq.com/350479720/blog/1349794552#!app=2&via=QZ.HashRefresh&pos=1349794552
	思路：动态规划，设dp[k][n]表示n个数逆序数为k的种类，
	则dp[0][n] = 1，表示从小到大排列，逆序数为0，只有1种
	考虑dp[k][n]，如何从 1 ~ n-1 的状态得到 1 ~ n 的状态
	    如果将n放在最后，那么没有新增逆序数，所以要获得k个逆序数，有dp[k][n-1]种
	    如果将n放在倒数第二，新增1个逆序数，所以要获得k个逆序数，有dp[k-1][n-1]种
	    ......
	    如果将n放在最前，新增n-1个逆序数，所以要获得k个逆序数，有dp[k+1-n][n-1]种
	即 dp[k][n] = dp[k][n-1] + dp[k-1][n-1] + dp[k-2][n-1] + ... + dp[k+1-n][n-1]种
	那么 dp[k+1][n] = dp[k+1][n-1] + dp[k][n-1] + dp[k-1][n-1] + ... + dp[k+2-n][n-1]种
	上下两式做减法，得
	dp[k+1][n] = dp[k][n] + dp[k+1][n-1] - dp[k+1-n][n-1]
	当k+1-n < 0时，可以认为dp[k+1-n][n-1]的值为0
	代码为了节省空间用了滚动数组，离线处理，先把所有请求记录，排序，然后按照顺序计算所有结果，
	再将结果按原来的序列输出。
*/


#include <stdio.h>
#include <algorithm>

using namespace std;

#define  MOD   1000000007
#define  MAXN  1001
#define  MAXK  20001
#define  MAXT  10000

// dp[k][n]，表示n个数逆序数为k的种类

int  dp[MAXK][2];
int  cnt = 1, f, t;

int  q[MAXT][2];
int  id[MAXT];
int  ans[MAXT];
	
void  init( int n ) {
	if( n == cnt - 1 ) return;

	int  k, e;
	for( ; cnt <= n; ++cnt ) {
		t = ( cnt & 1 ); f = 1 - t;
		dp[0][t] = 1;
		e = cnt * ( cnt - 1 ) / 2;
		if( e > MAXK ) e = MAXK;
		for( k = 1; k < e; ++k ) {
			dp[k][t] = dp[k-1][t] + dp[k][f];
			if( k >= cnt ) dp[k][t] -= dp[k-cnt][f];
			if( dp[k][t] >= MOD ) dp[k][t] -= MOD;
			if( dp[k][t] < 0 ) dp[k][t] += MOD;
		}
	}
}

inline
bool  cmp( const int & a, const int & b ) {
	return  q[a][0] < q[b][0];
}

int main() {
	int  T, i, n, k;

	for( scanf( "%d", &T ), i = 0; i < T; ++i ) {
		scanf( "%d%d", &q[i][0], &q[i][1] );
		id[i] = i;
	}
	sort( id, id + T, cmp );

	for( i = 0; i < T; ++i ) {
		n = q[ id[i] ][0], k = q[ id[i] ][1];
		init( n );
		ans[ id[i] ] = dp[k][t];
	}
	
	for( i = 0; i < T; ++i ) printf( "%d\n", ans[i] );
	return 0;
}
