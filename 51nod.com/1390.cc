/*
@author gogdizzy
@date   2015-08-19

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1390

@solution
	经推导，发现无法组成2和sum-2，其他都可以组成
	用贪心，每次尽可能多减，但是不要让剩下的结果是2即可。
*/

#include <iostream>
#include <math.h>

using namespace std;

#define LL long long

inline
LL min( LL a, LL b ) {
	return a < b ? a : b;
}

LL solve( LL x, LL y ) {

	if( x == 0 && y == 0 ) return 0;
	if( x == 2 || y == 2 ) return -1;

	LL m = (LL)sqrt( x + y );
	if( m * m != x + y ) return -1;


	LL ans = 0;
	LL n, p, d;
	while( x ) {
		n = min( m, ( x + 1 ) / 2 );
		if( n * n < x ) return -1;
		p = (LL) ( sqrt( n * n - x ) + 1.999999 );
		d = ( n * n - ( p - 1 ) * ( p - 1 ) );
		m = p - 1;

		if( x - d == 2 ) ++p;
		x -= ( n * n - ( p - 1 ) * ( p - 1 ) );
		ans += ( n - p + 1 );
	}

	return ans;
}

int main() {

	int t;
	LL  x, y;

	cin >> t;
	while( t-- ) {
		cin >> x >> y;
		cout << solve( x, y ) << endl;
	}

	return 0;
}
