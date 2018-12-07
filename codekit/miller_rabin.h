//
// Created by 关鑫 on 2018-12-06.
//
// 51nod 1186
#pragma once

#include <stdlib.h>

template < typename T >
bool miller_rabin( const T& p, int iter ) {

    if( !( p & 1 ) ) return false;  // even number

    T s = p - 1;
    int d = 0;
    while( !(s & 1) ) { s /= 2; ++d; }

    for( int i = 0; i < iter; ++i ) {
        a = rand() + 1;
        if( a == 1 ) continue;

        powmod( a, s, p, m );

        for( j = 0; j < d && !( m == one ) && !( m == pd1 ); ++j ) {
            mulmod( m, m, p, m );
        }
        if( !( m == pd1 ) && j > 0 ) return  false;
    }
    return  true;
}