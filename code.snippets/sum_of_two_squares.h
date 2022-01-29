//
// Created by 关鑫 on 2018-12-13.
//

#pragma once

#include <map>
#include <vector>
#include <algorithm>

template < typename T >
struct SumOfTwoSquares {
    std::vector< std::pair< T, T > > sums;

    void compute( T n ) {
        sums.clear();

        PollardRho <T> pr;
        pr.factorsize( n );

        std::map< T, int > facCnt;
        for( auto f : pr.factors ) ++facCnt[f];

        // 4k+3 prime odd times
        for( auto it : facCnt ) {
            if( it->first % 4 == 3 && it->second % 2 == 1 ) return;
        }

        std::vector< std::pair< T, T > > guassNums;
        for( auto it : facCnt ) {
            if( it->first == 2 ) {
                for( int i = 0; i < it->second; ++i ) guassNums.emplace_back( 1, 1 );
            }
            else if( it->first % 4 == 3 ) {
                for( int i = 0; i < it->second; ++i ) guassNums.emplace_back( it->first, 0 );
            }
            else {
                for( int i = 0; i < it->second; ++i ) guassNums.push_back( compute_4k1( it->first ) );
            }
        }

        // 各个因子的组合

    }

protected:
    static std::pair< T, T > compute_4k1( T p ) {
        T A = compute_sqrt( p ), B = 1;
        T M = ( A * A + 1 ) / p;
        while( M != 1 ) {
            T u = limit_mod( A, M );
            T v = limit_mod( B, M );
            T a = ( u * A + v * B ) / M;
            T b = ( u * B - v * A ) / M;
            A = a;
            B = b;
            M = ( A * A + B * B ) / p;
        }
    }

    static T limit_mod( T a, T b ) {
        T rv = a % b;
        if( rv > b / 2 ) rv -= b;
        else if( rv < b / 2 ) rv += b;
        return rv;
    }

    T compute_sqrt( T p ) {
        T p4 = ( p - 1 ) / 4;
        while( 1 ) {
            T a = rand() % ( p - 2 ) + 2;
            T A = powmod( a, p4, p );
            if( mulmod( A, A, p ) == p - 1 ) return A;
        }
    }
};
