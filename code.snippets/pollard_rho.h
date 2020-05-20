//
// Created by 关鑫 on 2018-12-06.
// https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm
// https://blog.csdn.net/xffyjq/article/details/52693369

#pragma once

template < typename T >
struct PollardRho {
    std::vector <T> factors;

    void factorsize( T n ) {
        while( !( n & 1 ) ) {
            factors.push_back( 2 );
            n /= 2;
        }

        if( MillerRabin< T >::test( n, 100 ) ) {
            factors.push_back( n );
            return;
        }

        T f;
        do {
            T base = rand() % ( n - 2 ) + 2;
            T c = rand() % ( n - 1 ) + 1;
            f = find1( n, base, c );
        } while( f == n );
        factorsize( f );
        factorsize( n / f );
    }


protected:
    T find1( const T &n, const T &base, const T &c ) {
        T x = base;
        T y = base;
        T d = 1;
        auto g = [ & ]( const T &x ) { return ( x * x + c ) % n; };
        while( d == 1 ) {
            x = g( x );
            y = g( g( y ) );
            d = gcd( ( x - y + n ), n );
        }
        return d;
    }

    T find2( const T &n, const T &base, const T &c ) {
        T x_fixed = base, x = base, d = 1;
        int size = 2;
        while( d == 1 ) {
            for( int count = 1; ( count <= size ) && ( d <= 1 ); ++count ) {
                x = ( x * x + c ) % n;
                d = gcd( x - x_fixed + n, n );
            }
            size = size * 2;
            x_fixed = x;
        }
        return d;
    }
};
