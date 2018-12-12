//
// Created by 关鑫 on 2018-12-12.
//

#pragma once

template < typename T >
T mulmod( const T& a, const T& b, const T& p ) {
    T ans = 1, tmp = a, b0 = b;
    while( b0 != 0 ) {
        if( b0 & 1 ) ans = ans * tmp % p;
        tmp = ( tmp + tmp ) % p;
        b0 /= 2;
    }
    return ans;
}

template < typename T >
T powmod( const T& a, const T& b, const T& p ) {
    T ans = 1, tmp = a, b0 = b;
    while( b0 != 0 ) {
        if( b0 & 1 ) ans = ans * tmp % p;
        tmp = tmp * tmp % p;
        b0 /= 2;
    }
    return ans;
}
