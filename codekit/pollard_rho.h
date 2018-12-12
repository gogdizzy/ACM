//
// Created by 关鑫 on 2018-12-06.
// https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm

#pragma once

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
