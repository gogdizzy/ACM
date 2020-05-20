//
// Created by 关鑫 on 2020/5/15.
//

#include <cstdio>
#include <algorithm>

using namespace std;

#define  MAXV  1001
#define  MAXE  50000

struct  edge_t {
    short  s;
    short  e;
    short  w;
};

inline
bool  cmp( const edge_t & a, const edge_t & b ) {
    return  a.w < b.w;
}

inline
short  find_father( short* father, short x ) {
    if( x != father[x] ) father[x] = find_father( father, father[x] );
    return  father[x];
}

int main() {
    int  n, m, i, ans = 0;
    edge_t  E[MAXE];
    short  father[MAXV];
    short  f1, f2;

    scanf( "%d%d", &n, &m );
    for( i = 1; i <= n; ++i ) father[i] = i;
    for( i = 0; i < m; ++i ) scanf( "%hd%hd%hd", &E[i].s, &E[i].e, &E[i].w );
    sort( E, E + m, cmp );
    for( i = 0; i < m && n > 1; ++i ) {
        f1 = find_father( father, E[i].s );
        f2 = find_father( father, E[i].e );
        if( f1 != f2 ) {
            ans += E[i].w;
            father[f2] = f1;
            --n;
        }
    }

    printf( "%d\n", ans );

    return 0;
}