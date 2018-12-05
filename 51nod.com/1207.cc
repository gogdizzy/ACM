/**
 * https://www.51nod.com/Challenge/Problem.html#!#problemId=1207
 * 内存管理
 * 思路：
 **/

#include <stdio.h>
#include <map>
#include <set>

class LineAllocator {

    using Map = std::map< int, int >;
    using Iter = Map::iterator;

public:
    LineAllocator( int ptr, int size ) {
        add( ptr, size );
    }

    int alloc( int size ) {
        if( size == 0 ) return 0;

        int ptr = -1;
        int len = 0;
        for( auto it = free_.begin(); it != free_.end(); ++it ) {
            if( it->second >= size ) {
                ptr = it->first;
                len = it->second;
                free_.erase( it );
                break;
            }
        }
        len -= size;
        if( len > 0 ) add( ptr + size, len );
        return ptr;
    }

    void free( int ptr, int size ) {
        if( size == 0 ) return;

        auto it = free_.lower_bound( ptr );
        if( it != free_.begin() ) --it;

        while( it != free_.end() ) {
            int ptr2 = it->first;
            int len2 = it->second;

            if( ptr2 > ptr + size ) break;
            if( ptr2 < ptr && ptr2 + len2 >= ptr ) {
                size += ptr - ptr2;
                ptr = ptr2;
                if( size < len2 ) size = len2;
            }
            else {
                int end2 = ptr2 + len2;
                if( end2 > ptr + size ) size = end2 - ptr;
            }
            it = remove( it );
        }
        add( ptr, size );
    }

protected:
    void add( int ptr, int size ) {
        free_.insert( std::make_pair( ptr, size ) );
    }

    Iter remove( Iter it ) {
        return free_.erase( it );
    }

private:
    Map free_; // ptr, len
};

int main() {
    freopen( "/Users/guanxin/Downloads/51nod_1207_4_in.txt", "rt", stdin );
    int n, m;
    int op, ptr, len;

    scanf( "%d%d", &n, &m );

    LineAllocator la( 0, n );

    for( int i = 0; i < m; ++i ) {
        scanf( "%d", &op );
        if( op == 1 ) {  // alloc
            scanf( "%d", &len );
            printf( "%d\n", la.alloc( len ) );
        }
        else { // free
            scanf( "%d%d", &ptr, &len );
            la.free( ptr, len );
        }
    }

    return 0;
}