/**
 * https://www.51nod.com/Challenge/Problem.html#!#problemId=1873
 * 初中的算数
 * 思路：模拟，不好写。。
 **/


#include <stdio.h>
#include <algorithm>

#define MAXD 6
#define MAXN 26

char a[MAXD + 1];
char buf[2][MAXD * MAXN + 1];

int main() {

    int n, d, dd;
    scanf( "%s%d", a, &n );

    char *p = strchr( a, '.' );
    char *e = strchr( a, '\0' );
    if( p ) {
        dd = e - p;
        for( char *q = p; q != e; ++q ) q[0] = q[1];
        --e;
    }
    else {
        dd = 0;
    }
    d = e - a;
    dd *= n;
    std::reverse( a, e );
    std::for_each( a, e, []( char & c ) { c -= '0'; } );

    int x = 0, y;
    buf[x][0] = 1;
    while( n-- ) {
        y = 1 - x;
        for( int i = 0; buf[x][i]; ++i ) {
            for( int j = 0; j < d; ++j ) {
                buf[y][i + j] += buf[x][i] * a[j];
                if( buf[y][i + j] > 9 ) {
                    buf[y][i + j + 1] += buf[y][i + j] / 10;
                    buf[y][i + j] %= 10;
                }
            }
        }
        x = y;
    }

    e = strchr( buf[x], '\0' );
    if( dd > 0 ) {
        p = buf[x] + dd;
        for( char *q = e - 1; q >= p; --q ) q[1] = q[0];
        *p = '.';
    }

    std::reverse( buf[x], e );


    return 0;
}

