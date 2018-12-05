/**
 * https://www.51nod.com/Challenge/Problem.html#!#problemId=1388
 * 六边形平面
 * 思路：如果存在X，至少需要1种颜色
 *      如果有相邻的，至少2种
 *      如果有组成三角形的，或者成奇数环的，至少3种
 **/


#include <stdio.h>
#include <string.h>

#define MAXN 50

char a[MAXN+2][MAXN+2];
int tbl[7] = { 0, 1, 0, 2, 0, 1, 0 };

inline int max2( int a, int b ) { return a > b ? a : b; }

int color( int x, int y ) {
    int mask = 0;
#define ADD_MASK( u, v ) do { \
    if( a[(v)][(u)] < 3 ) mask |= (1<<a[(v)][(u)]); \
} while( 0 )
    ADD_MASK( x, y - 1 );
    ADD_MASK( x + 1, y - 1 );
    ADD_MASK( x - 1, y );
    ADD_MASK( x + 1, y );
    ADD_MASK( x - 1, y + 1 );
    ADD_MASK( x, y + 1 );

    a[y][x] = tbl[mask];
    int ans = a[y][x] + 1;

#define EXPAND( u, v ) do { \
    if( a[(v)][(u)] == 'X' ) ans = max2( ans, color( (u), (v) ) ); \
} while( 0 )
    EXPAND( x, y - 1 );
    EXPAND( x + 1, y - 1 );
    EXPAND( x - 1, y );
    EXPAND( x + 1, y );
    EXPAND( x - 1, y + 1 );
    EXPAND( x, y + 1 );

    return ans;
}

int main() {

    int t, n;
    int ans;
    for( scanf( "%d", &t ); t--; ) {
        scanf( "%d%*c", &n );
        memset( a, '-', sizeof( a ) );
        for( int y = 1; y <= n; ++y ) {
            gets( &a[y][1] );
            a[y][n + 1] = '-';
        }

        ans = 0;
        for( int y = 1; y <= n; ++y ) {
            for( int x = 1; x <= n; ++x ) {
                if( a[y][x] == 'X' ) {
                    ans = max2( ans, color( x, y ) );
                }
            }
        }
        printf( "%d\n", ans );
    }

    return 0;
}
