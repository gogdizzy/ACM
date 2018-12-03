/**
 * https://www.51nod.com/Challenge/Problem.html#!#problemId=2020
 * 排序相减
 * 思路：模拟，查表
 **/

#include <stdio.h>
#include <algorithm>

#define MAXN 10000
#define MAXD 4

int tmax[MAXN];
int tmin[MAXN];

void init() {
    int d[MAXD];
    for( int i = 0; i < MAXN; ++i ) {
        int v = i;
        for( int k = 0; k < MAXD; ++k ) {
            d[k] = v % 10;
            v /= 10;
        }
        std::sort( d, d + MAXD );
        for( int k = 0; k < MAXD; ++k ) {
            tmin[i] = tmin[i] * 10 + d[k];
            tmax[i] = tmax[i] * 10 + d[MAXD - 1 - k];
        }
    }
}

int main() {
    init();

    int t, n, k;
    scanf( "%d", &t );
    while( t-- ) {
        scanf( "%d%d", &n, &k );
        while( k-- ) n = tmax[n] - tmin[n];
        printf( "%d\n", n );
    }
}
