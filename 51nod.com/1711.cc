//
// Created by 关鑫 on 2020/5/19.
//
// 1 统计前缀和
// 2 每个前缀和sum[i] - i * avg，如果这个值大于等于前面的某个值，那么它们之前的区间的平均值就大于等于avg
// 3 将数据离散化
// 3 依次放入离散值，统计前面出现过的小于等于当前数字的个数，用树状数组


#include <algorithm>
#include <iostream>
#include <iomanip>

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

long long sum[MAXN];
binary_indexed_tree_1d1mrq< int > bit( MAXN );
double a[MAXN];
double b[MAXN];

long long count( double x, int n ) {
    bit.reset();
    for( int i = 1; i <= n; ++i ) a[i] = b[i] = sum[i] - i * x;
    sort( a, a + n + 1 );
    int num = unique( a, a + n + 1 ) - a;
    long long ans = 0;
    for( int i = 0; i <= n; ++i ) {
        int pos = lower_bound( a, a + num, b[i] ) - a + 1;
        ans += bit.query( pos );
        bit.modify( pos, 1 );
    }
    return ans;
}

int main() {

    ios::sync_with_stdio( false );
    cin.tie( 0 );

    int n, x;
    long long k;

    cin >> n >> k;

    sum[0] = 0;
    for( int i = 1; i <= n; ++i ) {
        cin >> x;
        sum[i] = sum[i - 1] + x;
    }

    double l = 0, r = 100000.0, m;
    while( r - l > 1e-6 ) {
        m = ( l + r ) / 2.0;
        if( count( m, n ) >= k ) l = m;
        else r = m;
    }

    double ans = ( l + r ) / 2.0;
    cout << fixed << setprecision(4) << ans;

    return 0;
}

