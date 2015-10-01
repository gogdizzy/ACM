/*
@author gogdizzy
@date   2015-08-19

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1331

@solution
	这个题的数据量不大，可以简单的枚举到左出口的狼和右出口的狼，剩下的
	就是留在管道中的，必须保证留在管道中的恰好就是中间的，且顺序和最终
	一致。

	这个问题容易想漏的一点就是，有的狼也许到了某一个端点，又穿过整个管
	道，到了另一个端点。例如一个1000长的管道有5只狼，分别位于
		1,2,997,998,999
	目标是 2,3,998,999,1
	也就是前4只狼不需要动很远，只有最后一只离目标很远，这时一个比较好
	的方案是前两只到左出口，后3只到右出口，然后最后一只到左出口，再按序
	进入管道，总路程最短。

	当初始所有的狼都到了管道的两端，则枚举左边第一个进入管道并停留在
	管道中的狼fs，所有终点在fs右侧的都应该先到右端点，右边所有终点在
	fs左侧的都应该先到左端点。

	所以总的复杂度是O( n^3 )
*/
#include <stdio.h>
#include <algorithm>
using namespace std;
#define  MAXN  50

pair< int, int >  x[MAXN];  // first = start, second = end

inline
int abs( int x ) {
	return x < 0 ? -x : x;
}

int solve( int n, int l ) {

	sort( x, x + n );

	int  out_left, out_right;
	int  i, j, fs;
	int  tmp, ans = 0x7fffffff;
	bool ok = false;

	// [0,out_left]全部到左边，[out_right,n-1]全部到右边，剩下的留在管道中
	for( out_left = -1; out_left <= n - 1; ++out_left ) {
		for( out_right = out_left + 1; out_right <= n; ++out_right ) {

			ok = true;
			// 如果有留在中间的狼，那么他们应该有序，并且左边都小于他们，右边都大于他们
			if( out_right > out_left + 1 ) {
				tmp = 0;
				for( i = out_left + 1; i < out_right - 1; ++i ) {
					if( x[i].second >= x[i+1].second ) {
						ok = false;
						break;
					}
					tmp += abs( x[i].second - x[i].first );
				}
				tmp += abs( x[i].second - x[i].first );
				if( !ok ) continue;

				for( i = 0; i <= out_left; ++i ) {
					if( x[i].second >= x[out_left+1].second ) {
						ok = false;
						break;
					}
					tmp += x[i].first + x[i].second;
				}
				if( !ok ) continue;
				for( i = out_right; i < n; ++i ) {
					if( x[i].second < x[out_right-1].second ) {
						ok = false;
						break;
					}
					tmp += l + l - x[i].first - x[i].second;
				}
				if( !ok ) continue;
				if( tmp < ans ) ans = tmp;
			}
			else {
				// 现在狼全在两端
				// 枚举左边第一个进入管道并且停留的，则右边所有终点在它
				// 左侧的，都需要到左边来，左边所有终点在它右边的，都需要
				// 到右边去

				// 全在右边
				if( out_left == -1 ) {
					tmp = 0;
					for( i = 0; i < n; ++i ) tmp += l + l - x[i].first - x[i].second;
					if( tmp < ans ) ans = tmp;
				}
				// 当左边必然有狼时，枚举第一个stay的就可以了
				for( fs = 0; fs <= out_left; ++fs ) {
					tmp = 0;
					for( i = 0; i <= out_left; ++i ) {
						if( x[i].second <= x[fs].second ) tmp += x[i].first + x[i].second;
						else tmp += x[i].first + l + l - x[i].second;
					}
					for( i = out_right; i < n; ++i ) {
						if( x[i].second < x[fs].second ) tmp += l - x[i].first + l + x[i].second;
						else tmp += l - x[i].first + l - x[i].second;
					}
					if( tmp < ans ) ans = tmp;
				}
			}

		}
	}
	return ans;
}

int main() {

	int  t, n, l;
	int  i;

	for( scanf( "%d", &t ); t--; ) {
		scanf( "%d%d", &n, &l );
		for( i = 0; i < n; ++i ) scanf( "%d%d", &x[i].first, &x[i].second );
		printf( "%d\n", solve( n, l ) );
	}

	return 0;
}
