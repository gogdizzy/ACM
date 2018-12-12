/**
 * http://hihocoder.com/contest/hiho232/problem/1
 * 拆字游戏
 * 思路：每个块进行bfs搜索，用不同的数字标记，并记录boundBox
 **/


#include <stdio.h>
#include <vector>
#include <algorithm>

#define MAXN 500

int mat[MAXN+2][MAXN+2];

struct Rect {
    int startX, startY, endX, endY;
    int startY1;
    int tag;

    Rect() : startX( 0 ), startY( 0 ), endX( 0 ), endY( 0 ) {}
    Rect( int startX, int startY, int endX, int endY, int tag )
        : startX( startX ), startY( startY ), endX( endX ), endY( endY ), tag( tag ) {}
    void expand( int x, int y ) {
        if( x == startX && y < startY1 ) startY1 = y;
        if( x < startX ) startX = x, startY1 = y;
        if( y < startY ) startY = y;
        if( x > endX ) endX = x;
        if( y > endY ) endY = y;

    }
};

void bfs( int x, int y, Rect& rect ) {
    mat[y][x] = rect.tag;
    rect.expand( x, y );
    if( mat[y][x - 1] == 1 ) bfs( x - 1, y, rect );
    if( mat[y][x + 1] == 1 ) bfs( x + 1, y, rect );
    if( mat[y - 1][x] == 1 ) bfs( x, y - 1, rect );
    if( mat[y + 1][x] == 1 ) bfs( x, y + 1, rect );
}

int main() {
    int n, m;

    scanf( "%d%d%*c", &n, &m );

    for( int y = 1; y <= n; ++y ) {
        for( int x = 1; x <= m; ++x ) {
            mat[y][x] = getchar() - '0';
        }
        getchar();
    }

    int tag = 2;
    std::vector< Rect > rects;

    for( int y = 1; y <= n; ++y ) {
        for( int x = 1; x <= m; ++x ) {
            if( mat[y][x] == 1 ) {
                Rect r( MAXN + 1, MAXN + 1, 0, 0, tag++ );
                bfs( x, y, r );
                rects.push_back( r );
            }
        }
    }

    std::sort( rects.begin(), rects.end(), [](const Rect& a, const Rect& b) {
        return a.startX < b.startX || ( a.startX == b.startX && a.startY1 < b.startY1 );
    });

    for( auto r : rects ) {
        printf( "%d %d\n", r.endY - r.startY + 1, r.endX - r.startX + 1 );
        for( int y = r.startY; y <= r.endY; ++y ) {
            for( int x = r.startX; x <= r.endX; ++x ) {
                putchar( mat[y][x] == r.tag ? '1' : '0' );
            }
            putchar( '\n' );
        }
    }

    return 0;
}

