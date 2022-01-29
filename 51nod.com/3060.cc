//
// Created by 关鑫 on 2021/6/24.
//

#include <stdio.h>
#include <stdint.h>
#include <math.h>

const int MAXN = 32000;

int p[4000];  // about MAXN / ln( MAXN )
int pc = 0;
int f[MAXN/32+1];

#define  TEST( n )  ( f[n>>5] & (1<<(n&31) ) )
#define  SET( n )  ( f[n>>5] |= (1<<(n&31)) )

inline
void  sieve( int x ) {
    int  rt = (int)sqrt( (double)x ) + 1;
    for( int i = 2; i <= x; ++i ) {
        if( !TEST(i) ) {
            p[pc++] = i;
            if( i < rt ) for( int j = i * i; j <= x; j += i ) SET( j );
        }
    }
    p[pc++] = MAXN + 1;  // just a barrier, not prime
}

int factor[64];
int factorCnt[64];
int factorSize = 0;

void getFactors(int n) {
    for(int i = 0; p[i] <= n && i < pc; ++i) {
        if(n % p[i] == 0) {
            factor[factorSize] = p[i];
            do {
                ++factorCnt[factorSize];
                n /= p[i];
            } while(n % p[i] == 0);
            ++factorSize;
        }
    }
    if(n > 1) {
        factor[factorSize] = n;
        factorCnt[factorSize] = 1;
        ++factorSize;
    }
}

int n;
int ans = 0;

void dfs(int64_t cur, int pos) {
    if(cur > n) return;
    if(pos >= factorSize) {
        ++ans;
        return;
    }
    int64_t tmp = cur;
    for(int i = 0; i <= factorCnt[pos]; ++i) {
        dfs(tmp, pos + 1);
        tmp *= factor[pos];
    }
}

int main() {
    sieve(MAXN);

    scanf("%d", &n);

    getFactors(n);
    for(int i = 0; i < factorSize; ++i) factorCnt[i] *= 2;
    dfs(1, 0);

    printf("%d\n", ans);
    return 0;
}