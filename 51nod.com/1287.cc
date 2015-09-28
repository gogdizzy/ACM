/*
@author gogdizzy
@date   2015-08-19

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1287

@solution
	版本1
		用树状数组维护查询区间最大值，每次炮弹来，先二分查询能够挡住炮弹的
		墙的位置，然后更新。

		正常情况每次更新是 O( log(n)^2 )，但是因为数值只会变得越来越大，没
		必要更新子区域，只需要更新父节点，所以每次更新O( log(n) )
		单次查询是 O( log(n) )，但是我们要查询最开始能挡住炮弹的墙，用了
		一个二分，所以每次要 O( log(n)^2 )，整体复杂度是 n * O( log(n)^2 )

	版本2（copy鲨鱼代码）
		维护一个前缀最大值数组，这个数组是非递减的，如果来了一发炮弹，可以
		在这个数组中二分查找位置。我们想一下，炮弹落下来会发生什么？这时它
		一定落在一个前后有高度差的位置，前面的位置高度加1，可以更新前缀最
		大值数组，但是不会改变前缀数组的有序状态，即，前缀数组一直是非递减
		的。复杂度是 n * O( log(n) )

*/

#define VER2

#ifdef VER2

#include <stdio.h>
#include <algorithm>

#define MAXN 50000
#define MAX( a, b ) ( (a) > (b) ? (a) : (b) )

int h[MAXN];
int mx[MAXN];

int main() {

	int  m, n, i, x;

	scanf( "%d%d", &m, &n );

	for( i = 0; i < m; ++i ) {
		scanf( "%d", h + i );
	}

	mx[0] = h[0];
	for( i = 1; i < m; ++i ) {
		mx[i] = MAX( h[i], mx[i-1] );
	}

	for( i = 0; i < n; ++i ) {
		scanf( "%d", &x );
		if( mx[0] >= x || mx[m-1] < x ) continue;
		int pos = std::lower_bound( mx, mx + m, x ) - mx - 1;
		++h[pos];
		mx[pos] = MAX( h[pos], mx[pos] );
	}

	for( i = 0; i < m; ++i ) {
		printf( "%d\n", h[i] );
	}

	return 0;
}

#endif

#ifdef VER1

#include <functional>
#include <iterator>

// 用树状数组维护最值
// 需要存储两个数组，一个是原数组，一个是树状数组存区域最值
template< typename T, typename _Compare = std::less< T > >
class BIT_1D_MM {

public:
	template< typename Iter >
	BIT_1D_MM( Iter beg, Iter end, T initv = T() ) {
		int d = std::distance( beg, end );
		dim_ = d + 1;
		a_ = new T[dim_ + 1];
		m_ = new T[dim_ + 1];

		for( int i = 0; i <= dim_; ++i ) {
			a_[i] = initv;
			m_[i] = initv;
		}

		for( int i = 0; beg != end; ++i, ++beg ) {
			modify( i, *beg );
		}
	}

	BIT_1D_MM( int d, T initv = T() ) {
		dim_ = d + 1;
		a_ = new T[dim_ + 1];
		m_ = new T[dim_ + 1];

		for( int i = 0; i <= dim_; ++i ) {
			a_[i] = initv;
			m_[i] = initv;
		}
	}

	~BIT_1D_MM() {
		delete[] a_;
		a_ = nullptr;
		delete[] m_;
		m_ = nullptr;
	}

	void modify( int p, T v ) {
		++p;
		if( a_[p] == v ) return;
		else if( cmp_( v, a_[p] ) ) {
			a_[p] = v;
			for( int i = p; i <= dim_; i += lowbit( i ) ) {
				if( cmp_( v, m_[i] ) ) m_[i] = v;
			}
		}
		else {
			a_[p] = v;
			int lbi;
			for( int i = p; i <= dim_; i += lbi ) {
				m_[i] = v;
				lbi = lowbit( i );
				for( int j = 1; j < lbi; j <<= 1 ) {
					if( cmp_( m_[i-j], m_[i] ) ) m_[i] = m_[i-j];
				}
			}
		}
	}

	T query( int l, int r ) {
		++l, ++r;
		T ans = a_[r--];
		int lbr;
		while( l <= r ) {
			lbr = lowbit( r );
			if( r - lbr >= l ) {
				if( cmp_( m_[r], ans ) ) ans = m_[r];
				r -= lbr;
			}
			else {
				if( cmp_( a_[r], ans ) ) ans = a_[r];
				--r;
			}
		}
		return ans;
	}

protected:
	inline
	int lowbit( int x ) {
		return x & -x;
	}

private:
	_Compare cmp_;
	int dim_;
	T   *a_;
	T   *m_;
};

#include <stdio.h>

#define MAXH 1000000
#define MAXN 50000

int main() {

	int  m, n, i, x;

	BIT_1D_MM< int, std::greater< int > >  bit( MAXN, -1 );

	scanf( "%d%d", &m, &n );

	for( i = 0; i < m; ++i ) {
		scanf( "%d", &x );
		bit.modify( i, x );
	}

	for( i = 0; i < n; ++i ) {
		scanf( "%d", &x );
		if( bit.query( 0, 0 ) >= x ) continue;
		if( bit.query( 0, m - 1 ) < x ) continue;
		int left = 0, right = m - 1, mid;
		while( left < right ) {
			mid = ( left + right ) / 2;
			if( bit.query( left, mid ) >= x ) right = mid;
			else left = mid + 1;
		}
		--left;
		bit.modify( left, bit.query( left, left ) + 1 );
	}

	for( i = 0; i < m; ++i ) {
		printf( "%d\n", bit.query( i, i ) );
	}

	return 0;
}

#endif
