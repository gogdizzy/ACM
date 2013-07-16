/**
*  http://51nod.com/onlineJudge/questionCode.html#!problemId=1112
*  KGold
*  参考答案：http://51nod.com/question/index.html#!questionId=430
*  思路：
*    1 在起始点，各个初始值互不相同，先按照初始值排序，nlog(n)
*    2 每次超越，只会发生在相邻的两个人之间，计算相邻两人之间的相遇点（slope_t），放入set结构，O( nlog(n) )
*    3 每次找出最近的相遇点，交换相遇的两个人。例如ABCD中BC交换，变成了ACBD，那么
*      BC相遇了一次，那么以后不可能相遇了，直接删除，O( log(n) )。
*      AB暂时不能相遇，因为中间隔着C，同理CD暂时不能相遇，因为隔着B，所以删除AB和CD的相遇点，O( log(n) )。
*      AC可能相遇，BD可能相遇，分别判断，加入到set中，O( log(n) )。
*      因为一个相遇时间点可能有多个相遇，所以还要用ans缓存一下，排序输出。
*/

#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;

#define  MAXS  100
#define  MAXN  10000
#define  MAXA  10000

struct  person_t {
	int  id;
	int  beg;
	int  add;
};

struct  slope_t {
	int  numerator;
	int  denominator;
	int  pos;

	slope_t() {}
	slope_t( int n, int d, int p ) :
		numerator( n ), denominator( d ), pos( p )
	{}
	bool  equal_slope( const slope_t & x ) {
		return  numerator * (long long)x.denominator == denominator * (long long)x.numerator;
	}
	bool  operator == ( const slope_t & x ) {
		return  pos == x.pos && equal_slope( x );
	}
};

struct  ans_t {
	int  fast_id;
	int  slow_id;
};

inline
bool  cmp_beg( const person_t & a, const person_t & b ) {
	return  a.beg < b.beg;
}

struct  cmp_slope{
	bool operator ()( const slope_t & a, const slope_t & b ) {
		long long  c1 = a.numerator * (long long)b.denominator;
		long long  c2 = a.denominator * (long long)b.numerator;
		return   c1 < c2 || ( c1 == c2 && a.pos < b.pos );
	}
};

inline
bool  cmp_id( const ans_t & a, const ans_t & b ) {
	return  a.fast_id < b.fast_id || ( a.fast_id == b.fast_id && a.slow_id < b.slow_id );
}

int main() {
	int  n, i, tmp, cnt = 0;
	person_t  p[MAXN];
	ans_t  ans[MAXS*MAXS];
	int  acnt;
	set< slope_t, cmp_slope >  s;

	for( scanf( "%d", &n ), i = 0; i < n; ++i ) {
		p[i].id = i + 1;
		scanf( "%d%d", &p[i].beg, &p[i].add );
	}
	
	sort( p, p + n, cmp_beg );

#define  CHECK_INSERT( a, b, p ) do{ if( a.beg < b.beg && a.add > b.add ) \
	s.insert( slope_t( b.beg - a.beg, a.add - b.add, p ) ); }while(0)
#define  CHECK_REMOVE( a, b, p ) do{ if( a.beg < b.beg && a.add > b.add ) \
	s.erase( slope_t( b.beg - a.beg, a.add - b.add, p ) ); }while(0)

	for( i = 1; i < n; ++i ) {
		CHECK_INSERT( p[i-1], p[i], i );
	}
	if( s.size() == 0 ) { puts( "No Solution" ); return 0; }

	while( s.size() != 0 && cnt < MAXA ) {
		acnt = 0;

		slope_t  min = *s.begin(), tmp;

		while( s.size() != 0 &&
			min.equal_slope( ( tmp = *s.begin() ) ) ) {
			s.erase( s.begin() );
			ans[acnt].slow_id = p[tmp.pos].id;
			ans[acnt].fast_id = p[tmp.pos-1].id;
			++acnt;
			if( tmp.pos > 1 ) CHECK_REMOVE( p[tmp.pos-2], p[tmp.pos-1], tmp.pos - 1 );
			if( tmp.pos + 1 < n ) CHECK_REMOVE( p[tmp.pos], p[tmp.pos+1], tmp.pos + 1 );
			swap( p[tmp.pos], p[tmp.pos-1] );
			if( tmp.pos > 1 ) CHECK_INSERT( p[tmp.pos-2], p[tmp.pos-1], tmp.pos - 1 );
			if( tmp.pos + 1 < n ) CHECK_INSERT( p[tmp.pos], p[tmp.pos+1], tmp.pos + 1 );
		}

		if( acnt > 1 ) sort( ans, ans + acnt, cmp_id );
		for( i = 0; i < acnt && cnt < MAXA; ++i, ++cnt ) {
			printf( "%d %d\n", ans[i].fast_id, ans[i].slow_id );
		}
	}

	return 0;
}