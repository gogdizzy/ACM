/**
 * https://www.51nod.com/Challenge/Problem.html#!#problemId=1106
 * 质数检测
 * 思路：打表 或 miller-rabin
 **/

#define VER2

#ifdef VER2

#include <stdio.h>
#include <stdlib.h>

template< typename T >
T powmod( const T& a, const T& b, const T& p ) {
    T ans = 1, tmp = a, b0 = b;
    while( b0 != 0 ) {
        if( b0 & 1 ) ans = ans * tmp % p;
        tmp = tmp * tmp % p;
        b0 /= 2;
    }
    return ans;
}

template < typename T >
bool miller_rabin( const T &p, int iter ) {

    if( !( p & 1 ) ) return p == 2;  // even number

    T pd1 = p - 1, d = p - 1;
    int s = 0;
    while( !( d & 1 ) ) {
        d /= 2;
        ++s;
    }

    for( int i = 0; i < iter; ++i ) {
        T a = rand() + 1;
        if( a == 1 ) continue;

        T m = powmod( a, d, p );

        int r = 0;
        for( ; r < s && m != 1 && m != pd1; ++r ) {
            m = m * m % p;
        }
        if( r > 0 && m != pd1 ) return false;
    }
    return true;
}

int main() {

    int n, x;

    scanf( "%d", &n );
    while( n-- ) {
        scanf( "%d", &x );
        puts( miller_rabin<long long>( x, 1000 ) ? "Yes" : "No" );
    }
    return 0;
}

#endif

#ifdef VER1

#include <stdio.h>
#include <math.h>

#define  MAXP 31627

char  flag[MAXP+1];
int   prime[3402];
int   count = 0;

void  init_ptbl() {
    int  i, k, m;
    prime[count++] = 2;
    for( i = 3; i <= MAXP / 2; i += 2 ) {
        if( flag[i] == 1 ) continue;
        for( k = 2; ( m = i * k ) <= MAXP; ++k ) flag[m] = 1;
    }
    for( i = 3; i <= MAXP; i += 2 ) if( flag[i] == 0 ) prime[count++] = i;
}

int main() {
    int n, x, i, e;
    init_ptbl();

    scanf( "%d", &n );
    while( n-- ) {
        scanf( "%d", &x );
        if( ( x & 1 ) == 0 ) { puts( x == 2 ? "Yes" : "No" ); continue; }
        e = (int)sqrt( x ) + 1;
        for( i = 1; prime[i] <= e; ++i ) if( x % prime[i] == 0 ) break;
        puts( prime[i] <= e ? "No" : "Yes" );
    }
    return 0;
}

#endif


