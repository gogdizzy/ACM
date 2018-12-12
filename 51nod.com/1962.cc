/**
 * https://www.51nod.com/Challenge/Problem.html#!#problemId=1962
 * 区间计数
 * 思路：单调栈，记录每个值作为区间最大的控制范围，多个区间可以multimap(因为数值比较小，为了效率用了vector数组)
 *      然后两个序列陆续对比，即可统计出1出现的次数
 **/


#include <stdio.h>
#include <vector>

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

    template < typename _RandomAccessIterator >
    bool compute( _RandomAccessIterator first, _RandomAccessIterator last, MonoStack::DIR dir, bool includeEqual ) {
        auto len = last - first;
        if( len <= 0 ) return false;
        if( !memory_init( len ) ) return false;

        int top = -1;
        switch( dir ) {
            case DIR::LEFT_MIN: {
                stk_[++top] = -1;
                if( includeEqual ) MONOSTACK_LEFT_LOOP( >= );
                else
                    MONOSTACK_LEFT_LOOP( > );
                break;
            }
            case DIR::LEFT_MAX: {
                stk_[++top] = -1;
                if( includeEqual ) MONOSTACK_LEFT_LOOP( <= );
                else
                    MONOSTACK_LEFT_LOOP( < );
                break;
            }
            case DIR::RIGHT_MIN: {
                stk_[++top] = len;
                if( includeEqual ) MONOSTACK_RIGHT_LOOP( >= );
                else
                    MONOSTACK_RIGHT_LOOP( > );
                break;
            }
            case DIR::RIGHT_MAX: {
                stk_[++top] = len;
                if( includeEqual ) MONOSTACK_RIGHT_LOOP( <= );
                else
                    MONOSTACK_RIGHT_LOOP( < );
                break;
            }
            default:
                return false;
        }
        return true;
    }

    inline
    IntType get( size_t i ) { return m_[i]; }

    inline
    IntType operator[]( size_t i ) { return m_[i]; }

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

#define MAXN 350000

int a[MAXN];
int b[MAXN];

std::vector< std::pair< int, int > > rangeA[MAXN + 1];
std::vector< std::pair< int, int > > rangeB[MAXN + 1];

int main() {

    int n;
    scanf( "%d", &n );
    for( int i = 0; i < n; ++i ) scanf( "%d", a + i );
    for( int i = 0; i < n; ++i ) scanf( "%d", b + i );

    MonoStack< int > leftA, rightA, leftB, rightB;
    using DIR = MonoStack< int >::DIR;

    leftA.compute( a, a + n, DIR::LEFT_MIN, true );
    rightA.compute( a, a + n, DIR::RIGHT_MIN, true );
    leftB.compute( b, b + n, DIR::LEFT_MIN, true );
    rightB.compute( b, b + n, DIR::RIGHT_MIN, true );

    for( int i = 0; i < n; ++i ) {
        rangeA[a[i]].push_back( std::make_pair( leftA[i] + 1, rightA[i] - 1 ) );
        rangeB[b[i]].push_back( std::make_pair( leftB[i] + 1, rightB[i] - 1 ) );
    }

    long long ans = 0;
    for( int v = 1; v <= n; ++v ) {
        if( rangeA[v].size() > 0 && rangeB[v].size() > 0 ) {
            for( auto it1 = rangeA[v].cbegin(), it2 = rangeB[v].cbegin();
                 it1 != rangeA[v].cend() && it2 != rangeB[v].cend(); ) {
                int diff = std::min( it1->second, it2->second ) - std::max( it1->first, it2->first ) + 1;
                if( diff > 0 ) ans += (long long)diff * diff;
                if( it1->second > it2->second ) ++it2;
                else ++it1;
            }
        }
    }

    printf( "%lld\n", ans );

    return 0;
}
