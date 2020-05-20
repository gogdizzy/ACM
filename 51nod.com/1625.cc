//
// Created by 关鑫 on 2020/5/12.
// 枚举行

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <algorithm>

#define MAXN 10
#define MAXM 200

int64_t rowsum[MAXN];
int64_t colsum[MAXM];
int64_t colsum2[MAXM];
int32_t a[MAXN][MAXM];

int main() {
freopen("/Users/guanxin/Downloads/in.txt", "rt", stdin);
    int n, m, x, k;

    scanf( "%d%d%d%d", &n, &m, &x, &k );

    for( int i = 0; i < n; ++i ) {
        for( int j = 0; j < m; ++j ) {
            scanf( "%d", &a[i][j] );
            rowsum[i] += a[i][j];
            colsum[j] += a[i][j];
        }
    }

    int64_t sum0 = 0;
    for( int i = 0; i < n; ++i ) sum0 += rowsum[i];

    int diff;
    int ruse;
    int64_t xn = (int64_t)x * n;
    int64_t xm = (int64_t)x * m;
    int64_t ans = 0;
    for( int z = 0; z < (1 << n); ++z ) {
        diff = 0;
        ruse = 0;
        memcpy( colsum2, colsum, sizeof(int64_t) * m );
        for( int r = 0; r < n; ++r ) {
            if( (1 << r) & z ) {
                ++ruse;
                diff += xm - rowsum[r];
                for( int c = 0; c < m; ++c ) {
                    colsum2[c] += x - a[r][c];
                }
            }
        }
        std::sort( colsum2, colsum2 + m );
        for( int c = 0; c < m && c < k - ruse; ++c ) {
            if( xn > colsum2[c] ) diff += xn - colsum2[c];
            else break;
        }
        ans = std::max( ans, sum0 + diff );
    }

    printf( "%lld\n", ans );

    return 0;
}