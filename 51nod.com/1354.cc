/*
@author gogdizzy
@date   2015-11-02

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1354

@solution
	先找出k的所有因子（不仅仅是质因子），sqrt(k)复杂度
	对于每个因子，每次读入一个数，如果使用了这个数字y，那么有几个条件
		1 这个数能被k整除
		2 y可以整除待更新的因子，增加的个数就是该因子除以y对应的个数
	注意更新要从大到小，避免重复使用一个数字，例如当前读入3，如果从小到大
	那么可能更新3，然后又更新9，但是更新9的时候要用到3，而这个3是刚被更新
	过的
*/

#include <stdio.h>
#include <map>

using namespace std;
typedef map< int, int > MyMap;
#define MAXN 1000
#define MAXSQRTK 10000
#define P 1000000007

void get_factor( int k, MyMap& f ) {
	for( int i = 1; i * i <= k; ++i ) {
		if( k % i == 0 ) {
			f[i] = f[k/i] = 0;
		}
	}
}

int main() {

	int t, i, n, k, y;
	MyMap  factor;
	MyMap::reverse_iterator it;

	for( scanf( "%d", &t ); t--; ) {
		scanf( "%d%d", &n, &k );
		factor.clear();
		get_factor( k, factor );
		factor[1] = 1;

		for( i = 0; i < n; ++i ) {
			scanf( "%d", &y );
			if( k % y != 0 ) continue;
			for( it = factor.rbegin(); it != factor.rend(); ++it ) {
				if( it->first >= y && it->first % y == 0 ) {
					it->second = ( it->second + factor[it->first/y] ) % P;
				}
			}
		}
		printf( "%d\n", factor[k] );
	}

	return 0;
}
