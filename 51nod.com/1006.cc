/*
@author gogdizzy
@date   2015-09-22

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1006

@solution
	这是一道基础动态规划题，为了处理方便，假设字符串索引基于1
	设 dp[i][j] 表示 A[1..i]和B[1..j]最长公共子序列长度
	则有递推式 dp[i][j] =
		max{ dp[i-1][j-1] + ( A[i] == B[j] ? 1 : 0 ), dp[i][j-1], dp[i-1][j] }

	如果只是计算长度，那么可以用滚动数组的方式来节省内存
	如果需要输出最长公共子序列，那么就需要额外的一些处理了，下面讲述一下如何对内存
	进行优化

	第一个版本
		最简单方案，直接存储整个dp矩阵，那么需要O(N^2)空间，考虑数据范围，可以用short
		得到矩阵就可以逆推回去，判断当前长度来自于哪里

	第二个版本
		观察递推式，我们可以发现，其实每次递推，都来源于“左”、“上”、“左上”三个方向
		所以考虑求长度用滚动数组，O(2*N)，保存方位用3进制数，我是用一个uint8表示5个
		3进制，所以总共需要 N * ( N + 4 ) / 5 个uint8

	第三个版本
		对于“左上”这个方向，其实可以通过逆推时对原字符串的对应字符是否相等进行判断
		也就是只需要存储“左”，“上”两个方向，所以用2进制就可以了，共需要 
		N * ( N + 7 ) / 8个uint8

	第四个版本
		http://www.ics.uci.edu/~dan/pubs/p341-hirschberg.pdf
*/

#define VER4

#ifdef VER4


#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define  MAXN  1002
#define  MAX( a, b )  ( (a) > (b) ? (a) : (b) )
char  A[MAXN];
char  B[MAXN];
char  R[MAXN];

uint16_t  dp[2][MAXN];
uint16_t  L1[MAXN];
uint16_t  L2[MAXN];

// a and b start with 1
void  lcs_length( char* a, int alen, char* b, int blen, uint16_t* LL ) {
	int  prev = 0, now = 1;
	memset( &dp[0][1], 0, sizeof(uint16_t) * blen );
	for( int i = 1; i <= alen; ++i ) {
		for( int j = 1; j <= blen; ++j ) {
			if( a[i] == b[j] ) dp[now][j] = dp[prev][j-1] + 1;
			else dp[now][j] = MAX( dp[prev][j], dp[now][j-1] );
		}
		prev = 1 - prev; now = 1 - now;
	}
	memcpy( LL, &dp[prev][0], sizeof(uint16_t) * (blen + 1) );
}

void  lcs_length_rev( char* a, int alen, char* b, int blen, uint16_t* LL ) {
	int  prev = 0, now = 1;
	memset( &dp[0][1], 0, sizeof(uint16_t) * blen );
	for( int i = alen; i >= 1; --i ) {
		for( int j = 1, k = blen; j <= blen; ++j, --k ) {
			if( a[i] == b[k] ) dp[now][j] = dp[prev][j-1] + 1;
			else dp[now][j] = MAX( dp[prev][j], dp[now][j-1] );
		}
		prev = 1 - prev; now = 1 - now;
	}
	memcpy( LL, &dp[prev][0], sizeof(uint16_t) * (blen + 1) );
}

int  lcs( char* a, int alen, char* b, int blen, char* c ) {

	if( blen == 0 ) return 0;
	if( alen == 1 ) {
		for( int i = 1; i <= blen; ++i ) if( a[1] == b[i] ) { *c = a[1]; return 1; }
		return 0;
	}
	int  mid = alen / 2;
	lcs_length( a, mid, b, blen, L1 );
	lcs_length_rev( a + mid, alen - mid, b, blen, L2 );
	int  M = L1[0] + L2[blen];
	int  sum, minj = 0;
	for( int i = 1; i <= blen; ++i ) {
		sum = L1[i] + L2[blen - i];
		if( sum > M ) { M = sum; minj = i; }
	}
	int x = lcs( a, mid, b, minj, c );
	int y = lcs( a + mid, alen - mid, b + minj, blen - minj, c + x );
	return x + y;
}


int main() {
	int  i, j, k, ii, jj, kk;
	scanf( "%s%s", A + 1, B + 1 );

	R[ lcs( A, strlen(A + 1), B, strlen(B + 1), R ) ] = 0;

	puts( R );
	return 0;
}

#endif


#ifdef VER3

#include <stdio.h>
#include <stdint.h>

#define  MAXN  1002

char  A[MAXN];
char  B[MAXN];
char  R[MAXN];

const int UP = 0, LEFT = 1;
const uint8_t coe[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };
uint8_t  dir[MAXN][MAXN/8+1];
#define  SET_DIR( row, col, d ) do { dir[row][col>>3] += coe[col&7] * d; } while( 0 )
#define  GET_DIR( row, col )  ( ( dir[row][col>>3] >> ( col & 7 ) ) & 1 )

short  dp[2][MAXN];

int main() {
	int  i, j, k, d, v;
	scanf( "%s%s", A + 1, B + 1 );

	int  prev = 0, now = 1;
	for( i = 1; A[i]; ++i ) {
		for( j = 1; B[j]; ++j ) {
			if( A[i] == B[j] ) dp[now][j] = dp[prev][j-1] + 1;
			else if( dp[prev][j] > dp[now][j-1] ) { dp[now][j] = dp[prev][j]; d = UP; }
			else { dp[now][j] = dp[now][j-1]; d = LEFT; }
			SET_DIR( i, j, d );
		}
		prev = 1 - prev; now = 1 - now;
	}

	k = MAXN - 1;
	for( --i, --j; i > 0 && j > 0; ) {
		d = GET_DIR( i, j );
		if( A[i] == B[j] ) { R[--k] = A[i]; --i; --j; }
		else if( d == LEFT ) --j;
		else --i;
	}
	puts( R + k );
	return 0;
}

#endif


#ifdef VER2

#include <stdio.h>

#define  MAXN  1002

char  A[MAXN];
char  B[MAXN];
char  R[MAXN];

const int UPLEFT = 0, UP = 1, LEFT = 2;
const uint8_t coe[5][3] = {
	0, 1 * 1, 1 * 2,
	0, 3 * 1, 3 * 2,
	0, 9 * 1, 9 * 2,
	0, 27 * 1, 27 * 2,
	0, 81 * 1, 81 * 2
};
uint8_t  dir[MAXN][MAXN/5+1];
#define  SET_DIR( row, col, d ) do { dir[row][col/5] += coe[col%5][d]; } while( 0 )
#define  GET_DIR( row, col )  ( dir[row][col/5] / coe[col%5][1] % 3 )

short  dp[2][MAXN];

int main() {
	int  i, j, k, d, v;
	scanf( "%s%s", A + 1, B + 1 );

	int  prev = 0, now = 1;
	for( i = 1; A[i]; ++i ) {
		for( j = 1; B[j]; ++j ) {
			if( dp[prev][j] > dp[now][j-1] ) { dp[now][j] = dp[prev][j]; d = UP; }
			else { dp[now][j] = dp[now][j-1]; d = LEFT; }
			if( ( v = dp[prev][j-1] + ( A[i] == B[j] ) ) >
				dp[now][j] ) { dp[now][j] = v; d = UPLEFT; }
			SET_DIR( i, j, d );
		}
		prev = 1 - prev; now = 1 - now;
	}

	k = MAXN - 1;
	for( --i, --j; i > 0 && j > 0; ) {
		d = GET_DIR( i, j );
		if( d == UPLEFT ) { R[--k] = A[i]; --i; --j; }
		else if( d == LEFT ) --j;
		else --i;
	}
	puts( R + k );
	return 0;
}

#endif

#ifdef VER1

#include <stdio.h>

#define  MAXN  1002

char  A[MAXN];
char  B[MAXN];
char  R[MAXN];
short  dp[MAXN][MAXN];

short  max3( short a, short b, short c ) {
	if( a > b ) b = a;
	return  b > c ? b : c;
}

int main() {
	int  i, j, k;
	scanf( "%s%s", A + 1, B + 1 );
	for( i = 1; A[i]; ++i ) {
		for( j = 1; B[j]; ++j ) {
			dp[i][j] = max3( dp[i-1][j], dp[i][j-1], dp[i-1][j-1] + ( A[i]==B[j] ? 1 : 0 ) );
		}
	}

	--i; --j; k = MAXN - 1;
	while( i > 0 && j > 0 ) {
		if( A[i] == B[j] ) { R[--k] = A[i]; --i; --j; }
		else if( dp[i-1][j] > dp[i][j-1] ) --i;
		else  --j;
	}
	printf( "%s\n", R + k );
	return 0;
}

#endif
