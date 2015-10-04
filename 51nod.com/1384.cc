/*
@author gogdizzy
@date   2015-08-19

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1384

@solution
	可以直接用标准库next_permutation
	也可以自己实现，实现的方法如下
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>

// 从右向左找到第一个正序的相邻数，设为第k和第k+1
// 从k+1到n找大于a[k]的最小值，如果多个，取最右，然后置换它和a[k]
// 将a[k+1]~a[n]逆序
template< typename Iter >
bool permutation( Iter beg, Iter end ) {
	Iter e = end;
	bool rv = false;
	for( Iter k1 = --e; k1 != beg; --k1 ) {
		Iter k = k1;
		--k;
		if( *k < *k1 ) {
			Iter m = k1, k2 = k1;
			for( ++k2; k2 != end; ++k2 ) {
				if( *k2 > *k && *k2 <= *m ) m = k2;
			}
			std::iter_swap( k, m );
			std::reverse( k1, end );
			return true;
		}
	}
	
	return rv;
}

int main() {
	char s[10] = {0};
	gets( s );
	int n = strlen( s );
	std::sort( s, s + n );
	do {
		puts( s );
	} while( permutation( s, s + n ) );
	
	return 0;
}
