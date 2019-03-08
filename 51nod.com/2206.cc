/**
 * https://www.51nod.com/Challenge/Problem.html#!#problemId=2206
 * 低买高卖
 * 思路：贪心，每次查找最小值（多个选最左边的），然后查找这个最小值后面的最大值（多个选最左边的），去掉它们，重复，实现起来比较麻烦
 * 参考：https://blog.csdn.net/qian2213762498/article/details/81743033
 *      假设每天的股票都卖出，同时选择当天或者之前某天的作为买入，技巧就是在队列里塞入2个当天的买入，分三种情况：
 *      1 当天买入被选择0次，那么当天就是卖出
 *      2 当天买入被选择1次，那么当天就是误操作（抵消）
 *      3 当天买入被选择2次，那么当天就是买入
 **/


#define VER2

#ifdef VER1

//#include <stdio.h>
//#include <string.h>
//#include <queue>
//
//#define MAXN 200000
//
//int a[MAXN + 1];
//
//template < typename T >
//class binary_indexed_tree_1dmin {
//
//public:
//    binary_indexed_tree_1dmin( int maxlen,
//                               std::function< bool( T, T ) > cmp = std::less< T >() ) {
//        this->maxlen = maxlen;
//        a = new T[maxlen + 1];
//        m = new int[maxlen + 1];
//        std::memset( a, 0, sizeof(T) * (maxlen + 1) );
//        std::memset( m, 0, sizeof(int) * (maxlen + 1) );
//        this->cmp = cmp;
//    }
//
//    virtual ~binary_indexed_tree_1dmin() {
//        if( a != nullptr ) delete[] a;
//        if( m != nullptr ) delete[] m;
//    }
//
//    void modify( int p, T v ) {
//        if( cmp( v, a[p] ) ) {
//            a[p] = v;
//            // 更新所有父节点，如果更新到某处，无需更新，那么更高层的节点也无需更新
//            for( int i = p; i <= maxlen; i += lowbit( i ) ) {
//                if( cmp( v, a[m[i]] ) ) m[i] = p;
//                else break;
//            }
//        }
//        else {
//            T oldv = a[p];
//            a[p] = v;
//            // 之前的最值不是a[p]，现在a[p]更大，更不可能是最值
//            if( cmp( a[m[p]], oldv ) ) return;
//
//            int lbi;
//            for( int i = p; i <= maxlen; i += lbi ) {
//                // 如果m[i]的值没有更新，那么就不必检查父节点
//                bool out = true;
//                if( cmp( a[i], a[m[i]] ) ) {
//                    m[i] = i;
//                    out = false;
//                }
//                lbi = lowbit( i );
//                // 寻找i节点所有第一层子节点的最值
//                for( int j = 1; j < lbi; j <<= 1 ) {
//                    if( cmp( a[m[i - j]], a[m[i]] ) ) {
//                        m[i] = m[i - j];
//                        out = false;
//                    }
//                }
//                if( out ) break;
//            }
//        }
//    }
//
//    T query( int l, int r ) {
//        T ans = a[r--];
//        int lbr;
//        while( l <= r ) {
//            lbr = lowbit( r );
//            if( r - lbr >= l ) {
//                if( cmp( a[m[r]], ans ) ) ans = a[m[r]];
//                r -= lbr;
//            }
//            else {
//                if( cmp( a[r], ans ) ) ans = a[r];
//                --r;
//            }
//        }
//        return ans;
//    }
//
//    int query_idx( int l, int r ) {
//        int ans = r--;
//        int lbr;
//        while( l <= r ) {
//            lbr = lowbit( r );
//            if( r - lbr >= l ) {
//                if( cmp( a[m[r]], a[ans] ) ) ans = m[r];
//                r -= lbr;
//            }
//            else {
//                if( cmp( a[r], a[ans] ) ) ans = r;
//                --r;
//            }
//        }
//        return ans;
//    }
//
//protected:
//    inline int lowbit( int x ) {
//        return x & -x;
//    }
//
//private:
//    // 基于1，所以注意数组边界
//    // a[i]表示原来数组的值
//    // m[i]表示a[1..i]这个区间最值的索引
//
//    int maxlen;
//    T *a;
//    int *m;
//    std::function< bool( T, T ) > cmp;
//};
//
//using pair = std::pair< int, int >;
//
//struct cmp {
//    bool operator()( const pair &a, const pair &b ) const {
//        return a.first > b.first || ( a.first == b.first && a.second < b.second );
//    }
//};
//
//int main() {
//    freopen( "/Users/guanxin/Downloads/51nod_2206_2_in.txt", "rt", stdin );
//    int n;
//    scanf( "%d", &n );
//
//    std::priority_queue< pair, std::vector< pair >, cmp > qmin;
//    binary_indexed_tree_1dmin< int > bitmax( n, std::greater< int >() );
//
//    for( int i = 1; i <= n; ++i ) {
//        scanf( "%d", a + i );
//        qmin.push( std::make_pair( a[i], i ) );
//        bitmax.modify( i, a[i] );
//    }
//
//    long long ans = 0;
//    while( qmin.size() > 0 ) {
//        pair pr = qmin.top();
//        qmin.pop();
//        int minv = pr.first;
//        int maxidx = bitmax.query_idx( pr.second, n );
//        int maxv = a[maxidx];
//        if( maxv > minv ) {
//            // printf( "%d %d %d\n", minv, maxv, maxidx );
//            ans += maxv - minv;
//        }
//        bitmax.modify( maxidx, 0 );
//        a[maxidx] = 0;
//    }
//
//    printf( "%lld\n", ans );
//
//    return 0;
//}

#endif

#ifdef VER2

#include <stdio.h>
#include <queue>

int main() {

    std::priority_queue< int > q; //大根堆
    int n, x;
    scanf( "%d", &n );

    long long ans = 0;
    for( int i = 0; i < n; ++i ) {
        scanf( "%d", &x );//读入卖出收益
        q.push( -x );
        q.push( -x );
        ans += x + q.top();
        q.pop();
    }
    printf( "%lld\n", ans );
    return 0;
}

#endif