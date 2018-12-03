/**
 * http://hihocoder.com/problemset/problem/1015
 * KMP算法
 * 思路：裸KMP算法
 **/

#include <stdio.h>
#include <string.h>

#define MAXP 10000
#define MAXN 1000000

char p[MAXP+1];
char s[MAXN+1];

#include <vector>

template < typename T >
class KmpMatch {
public:
    static const int INVALID = INT_MIN;

    KmpMatch() : p( nullptr ) {
    }

    KmpMatch( const T* str, const T end ) {
        init( str, end );
    }

    void init( const T* str, const T end ) {
        next.clear();
        p = str;
        e = end;

        if( str[0] != end ) next.push_back( -1 );
        for( int i = 1; str[i] != end; ++i ) {
            int j = next[i - 1];
            while( j >= 0 && str[j + 1] != str[i] ) j = next[j];
            if( str[j + 1] == str[i] ) ++j;
            next.push_back( j );
        }
    }

    int find( const T* from, int startPos, int* startCmpPos ) {
        return 0;
    }

    std::vector< int > findAll( const T* s, int pos ) {
        std::vector< int > rv;

        int size = next.size();
        int startPos = pos;

        // 空串匹配所有的间隙
        if( size == 0 ) {
            for( startPos = pos; s[startPos] != e; ++startPos ) rv.push_back( startPos );
            rv.push_back( startPos );
        }
        else {
            for( int i = startPos, j = 0; s[i] != e; ++i, ++j ) {
                if( s[i] == p[j] ) {
                    if( j + 1 == size ) {
                        rv.push_back( startPos );
                        int delta = size - 1 - next.back();
                        startPos += delta;
                        j -= delta;
                    }
                }
                else {

                }
            }
        }

        return rv;
    }
private:
    const T* p;
    T e;
    std::vector< int > next;
};

int main() {
    KmpMatch< char > kmp;
    int n;
    scanf( "%d%*c", &n );
    while( n-- ) {
        scanf( "%s%s", p, s );
        kmp.init( p, '\0' );
        printf( "%d\n", kmp.findAll( s, 0 ).size() );
    }
    return 0;
}
