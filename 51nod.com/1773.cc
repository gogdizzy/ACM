//
// Created by 关鑫 on 2019-05-21.
//

/**
 * https://www.51nod.com/Challenge/Problem.html#!#problemId=1773
 * A国的贸易
 * 思路：统计每个城市收到的贡献
 */


#include <stdio.h>

#define MAXN 20
#define P 1000000007
#define ULL unsigned long long

int inc[1 << MAXN];
int base[1 << MAXN];

int main() {
    int n, t;
    int pow2[MAXN + 1];
    for( int i = 0; i <= MAXN; ++i ) pow2[i] = ( 1 << i );

    scanf( "%d%d", &n, &t );

    for( int i = 0; i < pow2[n]; ++i ) {
        scanf( "%d", base + i );
        for( int k = 0; k < n; ++k ) ++inc[i ^ pow2[k]];
    }

    for( int i = 0; i < pow2[n]; ++i ) {
        printf( "%llu ", ( base[i] + (ULL)inc[i] * t ) % P );
    }

    return 0;
}
