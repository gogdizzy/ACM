/**
 * https://www.51nod.com/Challenge/Problem.html#!#problemId=1489
 * 蜥蜴和地下室
 * 思路：dfs
 **/


#include <stdio.h>
#include <algorithm>

#define KILL( x, z ) ( (x) < 0 ? 0 : (x) / (z) + 1 )

int h[10];
int ans = 0x7FFFFFFF;

int dfs( int cur, int n, int a, int b ) {
    if( cur == n ) {
        return std::max( KILL( h[n - 1], a ), KILL( h[n], b ) );
    }
    int minball = KILL( h[cur - 1], b );
    int maxball = std::max( minball, KILL( h[cur], a ) );

    int rv = 0x7FFFFFFF;
    for( int ball = minball; ball <= maxball; ++ball ) {
        h[cur - 1] -= b * ball; h[cur] -= a * ball; h[cur + 1] -= b * ball;
        rv = std::min( rv, ball + dfs( cur + 1, n, a, b ) );
        h[cur - 1] += b * ball; h[cur] += a * ball; h[cur + 1] += b * ball;
    }
    return rv;
}

int main() {

    int n, a, b;
    scanf( "%d%d%d", &n, &a, &b );
    for( int i = 0; i < n; ++i ) scanf( "%d", h + i );

    printf( "%d\n", dfs( 1, n - 1, a, b ) );

    return 0;
}
