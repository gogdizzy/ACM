#include <stdio.h>
#include <stdint.h>
#include <algorithm>

#define MAXN 500001
#define P 1000000000
#define i64 int64_t
#define i32 int32_t

i32 a[MAXN];
i32 minj_presum[MAXN];
i32 maxj_presum[MAXN];
i32 minj_x_j_presum[MAXN];
i32 maxj_x_j_presum[MAXN];
i32 minj_x_maxj_presum[MAXN];
i32 minj_x_maxj_x_j_presum[MAXN];

void init_presum( int st, int r ) {
    minj_presum[st - 1] = 0;
    maxj_presum[st - 1] = 0;
    minj_x_j_presum[st - 1] = 0;
    maxj_x_j_presum[st - 1] = 0;
    minj_x_maxj_presum[st - 1] = 0;
    minj_x_maxj_x_j_presum[st - 1] = 0;
    i64 mn = a[st];
    i64 mx = a[st];
    for( int j = st; j <= r; ++j ) {
        if( a[j] < mn ) mn = a[j];
        if( a[j] > mx ) mx = a[j];
        minj_presum[j] = ( minj_presum[j - 1] + mn ) % P;
        maxj_presum[j] = ( maxj_presum[j - 1] + mx ) % P;
        minj_x_j_presum[j] = ( minj_x_j_presum[j - 1] + mn * j ) % P;
        maxj_x_j_presum[j] = ( maxj_x_j_presum[j - 1] + mx * j ) % P;
        minj_x_maxj_presum[j] = ( minj_x_maxj_presum[j - 1] + mn * mx ) % P;
        minj_x_maxj_x_j_presum[j] = ( minj_x_maxj_x_j_presum[j - 1] + mn * mx % P * j ) % P;
    }
}

int64_t dac( int l, int r ) {
    if( l == r ) return (i64)a[l] * a[l] % P;

    i64 ans = 0;
    int m = ( l + r ) / 2;
    init_presum( m + 1, r );

    i64 lmin = a[m];
    i64 lmax = a[m];
    int u = m, v = m, x;
    for( i64 i = m; i >= l; --i ) {
        if( a[i] < lmin ) lmin = a[i];
        if( a[i] > lmax ) lmax = a[i];
        while( u < r && a[u + 1] > lmin ) ++u;
        while( v < r && a[v + 1] < lmax ) ++v;

        x = std::min( u, v );
        if( x > m ) {
            ans = ( ans + lmin * lmax % P * ( ( m + x - i - i + 3 ) * ( x - m ) / 2 % P ) ) % P;
        }

        if( u < v ) {
            ans = ( ans + lmax * ( ( minj_x_j_presum[v] - minj_x_j_presum[u] ) -
                                   ( i - 1 ) * ( minj_presum[v] - minj_presum[u] ) % P ) ) % P;
        }
        else if( v < u ) {
            ans = ( ans + lmin * ( ( maxj_x_j_presum[u] - maxj_x_j_presum[v] ) -
                                   ( i - 1 ) * ( maxj_presum[u] - maxj_presum[v] ) % P ) ) % P;
        }

        x = std::max( u, v );
        if( x < r ) {
            ans = ( ans + ( minj_x_maxj_x_j_presum[r] - minj_x_maxj_x_j_presum[x] ) -
                    ( i - 1 ) * ( minj_x_maxj_presum[r] - minj_x_maxj_presum[x] ) % P ) % P;
        }
    }
    return ( ans + dac( l, m ) + dac( m + 1, r ) ) % P;
}

int main() {
    int n = 0;
    scanf( "%d", &n );
    for( int i = 1; i <= n; ++i ) {
        scanf( "%d", a + i );
    }
    printf( "%lld", ( dac( 1, n ) + P ) % P );
    return 0;
}