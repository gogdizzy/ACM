/*
问题：
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1204
	http://acm.timus.ru/problem.aspx?space=1&num=1003
解答：
	用并查集，任何一次输入，都是将集合合并的操作。
	集合的top-father的定义就是这个集合中最前面的点。每个点开始时自己单独为一个集合，father就是自己。
	每个点对应一个val值，这个值的含义是father点到本点的奇偶性。初始化为0

	对于这个题目，只是统计区间的奇偶个数，如果两个区间没有overlap，是无法推出矛盾的；
	如果两个区间有overlap，但是没有前后对齐，也是无法推出矛盾的，例如1-2之间有奇数个，2-3之间有奇数个，
	那么当arr[2]==1时，arr[1]==arr[3]==0；arr[2]==0时，arr[1]==arr[3]==1

	所以要想推出矛盾，必需在一个集合中推出矛盾，也就是说，在某一次合并的时候，top-father一致（这相当于左端对齐了），
	但是推出奇偶矛盾。

	如果将奇数看成1，偶数看成0，那么奇偶的加减法和bit0和bit1的异或是同一个操作。
*/

#include <cstdio>
#define  MAXN  100001

int  ufs[MAXN];
char  val[MAXN];

int  find( int x ) {
	if( ufs[x] == x ) return x;
	int  ans = find( ufs[x] );
	val[x] ^= val[ufs[x]];
	return  ufs[x] = ans;
}

int main() {
	int  n, q, i, ans = -1, a, b;
	char  oe[8], v;
	scanf( "%d%d", &n, &q );
	for( i = 0; i <= n; ++i ) ufs[i] = i;
	for( i = 1; i <= q; ++i ) {
		scanf( "%d%d%s", &a, &b, oe );
		--a;  v = ( (oe[0]>>1)&1 );
		int  af = find( a ), bf = find( b );
		if( af == bf && ( val[a] ^ v ) != val[b] ) { ans = i; break; }
		else if( af < bf ) ufs[bf] = af, val[bf] = val[a] ^ val[b] ^ v;
		else ufs[af] = bf, val[af] = val[a] ^ val[b] ^ v;
	}
	for( ++i; i <= q; ++i ) scanf( "%d%d%s", &a, &b, oe );
	printf( "%d\n", ans );
	return 0;
}
