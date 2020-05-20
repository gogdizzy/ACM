//
// Created by 关鑫 on 2020/5/19.
//


#include <iostream>
#include <cstring>

using namespace std;

#define MAXN 100005

template < typename T >
class binary_indexed_tree_1d1mrq {

public:
    binary_indexed_tree_1d1mrq( int maxlen ) {
        this->maxlen = maxlen;
        bit_a = new T[maxlen + 1];
        reset();
    }

    virtual ~binary_indexed_tree_1d1mrq() {
        if( bit_a != nullptr ) delete[] bit_a;
    }

    void reset() {
        memset( bit_a, 0, sizeof(T) * (maxlen + 1 ) );
    }

    inline int lowbit( int x ) { return x & -x; }

    // 修改点x的值，加v
    inline void modify( int x, T v ) {
        for( ; 0 < x && x <= maxlen; x += lowbit( x ) ) {
            bit_a[x] += v;
        }
    }

    // 查询a[1..x]的和
    inline T query( int x ) {
        T s = T();
        for( x = x > maxlen ? maxlen : x; x > 0; x -= lowbit( x ) ) {
            s += bit_a[x];
        }
        return s;
    }

    // 查询a[x1..x2]的和
    inline T query( int x1, int x2 ) {
        return query( x2 ) - query( x1 - 1 );
    }

private:
    // 基于1，所以注意数组边界
    // a[i]表示原来数组的值
    // bit_a就是在a的基础上做树状数组
    int maxlen;
    T *bit_a;
};

long long a[MAXN];
binary_indexed_tree_1d1mrq< int > bit1( MAXN * 2 );
binary_indexed_tree_1d1mrq< int > bit2( MAXN * 2 );

long long count( long long x, int n ) {
    bit1.reset();
    bit2.reset();
    bit2.modify( MAXN, 1 );
    long long sum = 0, ans = 0;
    for( int i = 1; i <= n; ++i ) {
        if( a[i] >= x ) ++sum;
        else --sum;
        if( i & 1 ) {
            ans += bit2.query( sum + MAXN );
            bit1.modify( sum + MAXN, 1 );
        }
        else {
            ans += bit1.query( sum + MAXN );
            bit2.modify( sum + MAXN, 1 );
        }
    }
    return ans;
}

int main() {
freopen( "/Users/guanxin/Downloads/in.txt", "rt", stdin );
    ios::sync_with_stdio( false );
    cin.tie( 0 );

    int n, ans = 0;
    long long k;

    cin >> n >> k;

    for( int i = 1; i <= n; ++i ) {
        cin >> a[i];
    }

    long long l = 0, r = 1LL << 32, m;
    while( l + 1 < r ) {
        m = ( l + r ) / 2;
        if( count( m, n ) >= k ) l = m;
        else r = m;
    }

    cout << l << '\n';

    return 0;
}