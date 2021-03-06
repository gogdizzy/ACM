/**
 * http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1215
 * 数组的宽度
 * 思路：查找每个数组作为最大值和最小值的影响范围，直接累加到一起
 **/


#define VER2

#ifdef VER2

#include <stdio.h>

#define MAXN 50000

int a[MAXN];

template < typename IntType = int >
class MonoStack {
public:
    enum DIR {
        LEFT_MIN,
        LEFT_MAX,
        RIGHT_MIN,
        RIGHT_MAX
    };

    MonoStack() : m_( nullptr ), stk_( nullptr ) {}
    ~MonoStack() {
        if( m_ ) delete[] m_;
        if( stk_ ) delete[] stk_;
    }

#define MONOSTACK_LEFT_LOOP( OP ) do { \
    for( IntType i = 0; i < len; ++i ) { \
        auto tmp = *( first + i ); \
        while( stk_[top] != -1 && tmp OP *( first + stk_[top] ) ) --top; \
        m_[i] = stk_[top]; \
        stk_[++top] = i; \
    } \
} while( 0 )

#define MONOSTACK_RIGHT_LOOP( OP ) do { \
    for( IntType i = len - 1; i >= 0; --i ) { \
        auto tmp = *( first + i ); \
        while( stk_[top] != len && tmp OP *( first + stk_[top] ) ) --top; \
        m_[i] = stk_[top]; \
        stk_[++top] = i; \
    } \
} while( 0 )

    template< typename _RandomAccessIterator >
    bool compute( _RandomAccessIterator first, _RandomAccessIterator last, MonoStack::DIR dir, bool includeEqual ) {
        auto len = last - first;
        if( len <= 0 ) return false;
        if( !memory_init( len ) ) return false;

        int top = -1;
        switch( dir ) {
            case DIR::LEFT_MIN: {
                stk_[++top] = -1;
                if( includeEqual ) MONOSTACK_LEFT_LOOP( >= );
                else MONOSTACK_LEFT_LOOP( > );
                break;
            }
            case DIR::LEFT_MAX: {
                stk_[++top] = -1;
                if( includeEqual ) MONOSTACK_LEFT_LOOP( <= );
                else MONOSTACK_LEFT_LOOP( < );
                break;
            }
            case DIR::RIGHT_MIN: {
                stk_[++top] = len;
                if( includeEqual ) MONOSTACK_RIGHT_LOOP( >= );
                else MONOSTACK_RIGHT_LOOP( > );
                break;
            }
            case DIR::RIGHT_MAX: {
                stk_[++top] = len;
                if( includeEqual ) MONOSTACK_RIGHT_LOOP( <= );
                else MONOSTACK_RIGHT_LOOP( < );
                break;
            }
            default:
                return false;
        }
        return true;
    }

    inline
    IntType get( size_t i ) { return m_[i]; }

protected:
    bool memory_init( size_t need ) {
        if( m_ ) delete[] m_;
        if( stk_ ) delete[] stk_;
        m_ = new IntType[need];
        stk_ = new IntType[need + 1];
        return m_ != nullptr && stk_ != nullptr;
    }

private:
    IntType *m_;
    IntType *stk_;
};

int main() {

    int n;
    long long ans = 0;
    MonoStack< int > left, right;
    using DIR = MonoStack< int >::DIR;

    scanf( "%d", &n );
    for( int i = 0; i < n; ++i ) scanf( "%d", a + i );

    left.compute( a, a + n, DIR::LEFT_MIN, false );
    right.compute( a, a + n, DIR::RIGHT_MIN, true );

    for( int i = 0; i < n; ++i ) {
        ans += (long long) a[i] * ( i - left.get( i ) ) * ( right.get( i ) - i );
    }

    left.compute( a, a + n, DIR::LEFT_MAX, false );
    right.compute( a, a + n, DIR::RIGHT_MAX, true );

    for( int i = 0; i < n; ++i ) {
        ans -= (long long) a[i] * ( i - left.get( i ) ) * ( right.get( i ) - i );
    }

    printf( "%lld\n", ans );

    return 0;
}

#endif







#ifdef VER1

#include <stdio.h>

#define MAXN 50002
#define MAXV 50001
#define MINV 0

int a[MAXN];
int l[MAXN], r[MAXN];
int stk[MAXN], top;

int main() {

    int n;
    long long ans = 0;

    scanf( "%d", &n );
    for( int i = 1; i <= n; ++i ) scanf( "%d", a + i );

    a[0] = MAXV;
    top = -1;
    stk[++top] = 0;
    for( int i = 1; i <= n; ++i ) {
        while( a[i] > a[stk[top]] ) --top;
        l[i] = stk[top];
        stk[++top] = i;
    }

    a[n+1] = MAXV;
    top = -1;
    stk[++top] = n + 1;
    for( int i = n; i > 0; --i ) {
        while( a[i] >= a[stk[top]] ) --top;
        r[i] = stk[top];
        stk[++top] = i;
    }

    for( int i = 1; i <= n; ++i ) {
        ans += (long long) a[i] * ( i - l[i] ) * ( r[i] - i );
    }

    a[0] = MINV;
    top = -1;
    stk[++top] = 0;
    for( int i = 1; i <= n; ++i ) {
        while( a[i] < a[stk[top]] ) --top;
        l[i] = stk[top];
        stk[++top] = i;
    }

    a[n+1] = MINV;
    top = -1;
    stk[++top] = n + 1;
    for( int i = n; i > 0; --i ) {
        while( a[i] <= a[stk[top]] ) --top;
        r[i] = stk[top];
        stk[++top] = i;
    }

    for( int i = 1; i <= n; ++i ) {
        ans -= (long long) a[i] * ( i - l[i] ) * ( r[i] - i );
    }

    printf( "%lld\n", ans );

    return 0;
}

#endif