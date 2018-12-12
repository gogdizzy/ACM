//
// Created by 关鑫 on 2018-12-06.
//
// 参考 https://zh.wikipedia.org/wiki/%E7%B1%B3%E5%8B%92-%E6%8B%89%E5%AE%BE%E6%A3%80%E9%AA%8C
// 51nod 1186
#pragma once

#include <stdlib.h>

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
                // m = mulmod( m, m, p );
                m = m * m % p;
            }
            if( r > 0 && m != pd1 ) return false;
        }
        return true;
    }
};
