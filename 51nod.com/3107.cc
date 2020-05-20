//
// Created by 关鑫 on 2020/4/28.
//

#include <stdio.h>
#include <algorithm>

#define MAXN 100000
#define MAXM 100000

int a[MAXN];
int p[MAXN];

struct X {
    int a, b, c;
} x[MAXM];


int main() {
    int n, m;
    scanf( "%d %d", &n, &m );
    for( int i = 0; i < n; ++i ) {
        scanf( "%d", a + i );
        p[i] = i;
    }
    for( int i = 0; i < m; ++i ) {
        scanf( "%d %d %d", &x[i].a, &x[i].b, &x[i].c );
        // if( x[i].a < x[i].b ) std::swap( x[i].a, x[i].b );
    }
    std::sort( p, p + n, [&]( const int &x, const int &y ) { return a[x] < a[y]; } );
    std::sort( x, x + m, [&]( const X &x, const X &y ) {
        return a[x.c] < a[y.c] || (a[x.c] == a[y.c] && a[x.a] < a[y.a]);
    } );

    int k = 0;
    for( int i = 0; i < n; ++i ) {
        while( i >= x[k].a )
    }

    for( int i = 0; i < n; ++i ) {
        printf( "%d ", a[i] );
    }

    return 0;
}
