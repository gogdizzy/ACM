/**
 * http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1627
 * 瞬间移动
 * 思路：随便给个4*4的矩阵
 * 0 0 0 0
 * 0 1 1 1
 * 0 1 2 3
 * 0 1 3 6
 * 可以看出很像杨辉三角，下面证明
 * 对于任何一个点(x,y) | x>=2,y>=2 我们都有 ans(x,y) = 1 + sigma( ans(i,j) ) | i=0..x-1, j=0..y-1
 * 既每个点的值，等于它左上方矩形的数字和再加上1，1表示从起点可以1步到达，但是起点是0
 * 为了方便计算，并且不影响答案的情况下（不会询问起点），改写矩阵
 * 1 0 0 0
 * 0 1 1 1
 * 0 1 2 3
 * 0 1 3 6
 * 这样就有ans(x,y) = sigma( ans(i,j) ) | i=0..x-1, j=0..y-1
 * 可以发现ans(x-1,y)和ans(x,y-1)重叠的部分加起来等于ans(x-1,y-1)，而相对于ans(x,y)，他们恰好也没统计ans(x-1,y-1)
 * 所以ans(x,y) = ans(x-1,y) + ans(x,y-1) - ans(x-1,y-1) + ans(x-1,y-1)
 *             = ans(x-1,y) + ans(x,y-1)
 * 恰好就是杨辉三角递推式
 * 第2行第2列对应C(0,0)，每往下一行或者向右一列，都对应杨辉三角的下一行
 * 因为这个数字很大，所以需要边算边取模，要用到乘法逆元
 **/

#include <stdio.h>

#define ULL unsigned long long
#define P 1000000007

template <typename T>
T exgcd( T a, T b, T& x, T& y ) {
	if( b == 0 ) {
		x = 1; y = 0;
		return a;
	}
	T ans = exgcd( b, a % b, y, x );
	y -= a / b * x;
	return ans;
}

ULL comb( int n, int m ) {
	if( m > n / 2 ) m = n - m;
	ULL ans = 1;
	int x, y;
	for( int i = n, j = 1; j <= m; ++j, --i ) {
		exgcd( j, P, x, y );
		while( x < 0 ) x += P;
		ans = ans * i % P * x % P;
	}
	return ans;
}

int main() {
	int m, n;
	scanf( "%d%d", &m, &n );
	printf( "%llu\n", comb( m + n - 4, m - 2 ) );
	return 0;
}

