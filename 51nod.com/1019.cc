/*
@author gogdizzy
@date   2015-08-19

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1019

@solution
	方案1 归并排序，在排序过程中统计逆序数
	方案2 用树状数组，先将数值离散化，然后从后向前插入数字，
		每次插入之前，都统计一下比当前值小的数字个数加入答案
		插入时只要在该数值的地方加1
*/


#ifdef VER1

#include <stdio.h>
#include <string.h>

#define MAXN 50000
#define ULL unsigned long long

int  a[MAXN], b[MAXN];
ULL  merge_sort( int left, int right ) {
	ULL	cnt = 0;
	int	mid, i, j, k;
	if( left < right ) {
		mid = ( left + right ) / 2;
		cnt += merge_sort( left, mid ) + merge_sort( mid + 1, right );
		i = left, j = mid + 1, k = left;
		while( i <= mid && j <= right ) {
			if( a[i] <= a[j] ) b[k++] = a[i++];
			else {
				b[k++] = a[j++];
				cnt += j - k;
			}
		}
		memcpy( b + k, a + i, sizeof(int) * ( mid + 1 - i ) );
		memcpy( b + k, a + j, sizeof(int) * ( right + 1 - j ) );
		memcpy( a + left, b + left, sizeof(int) * ( right + 1 - left ) );
	}
	return cnt;
}

int main() {
	int	n, i;
	scanf( "%d", &n );
	for( i = 0; i < n; ++i ) scanf( "%d", a + i );
	printf( "%llu\n", merge_sort( 0, n - 1 ) );
	return 0;
}

#endif

#ifdef VER2

#include <stdio.h>
#include <stdint.h>
#include <algorithm>
using namespace std;

#define  MAXN  50000
#define  LOWBIT( x )  ( (x) & -(x) )

struct data_t {
	uint16_t  idx;
	union {
		int32_t  value;
		struct {
			uint16_t  compact;
			uint16_t  bit;
		};
	};
};

data_t  d[MAXN+1];
int     n;

void  modify_up( int i, int v ) {
	for( ; i <= n; i += LOWBIT(i) ) d[i].bit += v;
}

uint32_t  query_down( int i ) {
	uint32_t  ans = 0;
	for( ; i > 0; i -= LOWBIT(i) ) ans += d[i].bit;
	return ans;
}


bool  cmpv( const data_t & a, const data_t & b ) { return a.value < b.value || a.value == b.value && a.idx < b.idx; }
bool  cmpi(const data_t & a, const data_t & b ) { return a.idx > b.idx; }

int main() {
	int  i, x, y;
	uint32_t  ans = 0;

	for( scanf( "%d", &n ), i = 1; i <= n; ++i ) {
		scanf( "%d", &d[i].value );
		d[i].idx = i;
	}

	std::sort( d + 1, d + n + 1, cmpv );

	x = d[1].value; y = 1;
	for( i = 1; i <= n; ++i ) {
		if( d[i].value == x ) d[i].value = y;
		else { x = d[i].value; d[i].value = ++y; }
	}

	std::sort( d + 1, d + n + 1, cmpi );

	for( i = 1; i <= n; ++i ) {
		ans += query_down( d[i].compact - 1 );
		modify_up( d[i].compact, 1 );
	}

	printf( "%u\n", ans );
	return 0;
}

#endif
