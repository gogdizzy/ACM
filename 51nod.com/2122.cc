/**
 * https://www.51nod.com/Challenge/Problem.html#!#problemId=2122
 * 分解质因数
 * 思路：试除法 或 pollard-rho
 **/


#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

template < typename T >
struct MillerRabin {
    static bool test( const T &p, int iter ) {

        if( !( p & 1 ) ) return p == 2;  // even number

        T pd1 = p - 1, d = p - 1;
        int s = 0;
        while( !( d & 1 ) ) {
            d /= 2;
            ++s;
        }

        for( int i = 0; i < iter; ++i ) {
            T a = rand() % ( p - 2 ) + 1;
            if( a == 1 ) continue;

            T m = powmod( a, d, p );

            int r = 0;
            for( ; r < s && m != 1 && m != pd1; ++r ) {
                m = m * m % p;
            }
            // printf( "a = %lld r = %lld m = %lld\n", a, r, m );
            if( r > 0 && m != pd1 ) return false;
        }
        return true;
    }

protected:
    static T powmod( const T& a, const T& b, const T& p ) {
        T ans = 1, tmp = a, b0 = b;
        while( b0 != 0 ) {
            if( b0 & 1 ) ans = ans * tmp % p;
            tmp = tmp * tmp % p;
            b0 /= 2;
        }
        return ans;
    }
};

template <typename T>
T gcd( T a, T b ) {
    return b == 0 ? a : gcd( b, a % b );
}

template < typename T >
struct PollardRho {
    std::vector< T > factor;

    void factorize( T n ) {
        while( !( n & 1 ) ) {
            factor.push_back( 2 );
            n /= 2;
        }

        if( MillerRabin<T>::test( n, 100 ) ) {
            factor.push_back( n );
            return;
        }

        T f;
        do {
            T base = rand() % ( n - 2 ) + 2;
            T c = rand() % ( n - 1 ) + 1;
            f = find1( n, base, c );
        } while( f == n );
        factorize( f );
        factorize( n / f );
    }


protected:
    T find1( const T& n, const T& base, const T& c ) {
        T x = base;
        T y = base;
        T d = 1;
        auto g = [&]( const T& x ) { return ( x * x + c ) % n; };
        while( d == 1 ) {
            x = g( x );
            y = g( g( y ) );
            d = gcd( ( x - y + n ), n );
        }
        return d;
    }
};

int main() {
    int n;
    scanf( "%d", &n );

    // printf( "%d\n", MillerRabin<long long>::test( n, 100 ) );

    PollardRho<long long> pr;
    pr.factorize( n );

    std::sort( pr.factor.begin(), pr.factor.end() );

    for( auto p : pr.factor ) {
        printf( "%lld\n", p );
    }

    return 0;
}
