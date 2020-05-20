//
// Created by 关鑫 on 2018-11-29.
//

#pragma once

void kmp( const char* s, int len, int* n ) {
    // s[0] is a sentinel
    // s[1..n[i]] is suffix of s[1..i]
    n[1] = 0;
    for( int i = 2; i <= len; ++i ) {
        int j = n[i - 1];
        while( j && s[j + 1] != s[i] ) j = n[j];
        if( s[j + 1] == s[i] ) ++j;
        n[i] = j;
    }
}

void kmp( const char* s, int len, int* n ) {
    // s[0..n[i]] is suffix of s[0..i]
    n[0] = -1;
    for( int i = 1; i < len; ++i ) {
        int j = n[i - 1];
        while( j >= 0 && s[j + 1] != s[i] ) j = n[j];
        if( s[j + 1] == s[i] ) ++j;
        n[i] = j;
    }
}

#include <vector>

template < typename T >
class KmpMatch {
public:
    KmpMatch() : p( nullptr ) {
    }

    KmpMatch( const T* str, const T end ) {
        init( str, end );
    }

    ~KmpMatch() {
        if( next != nullptr ) delete[] next;
    }

    void init( const T* str, const T end ) {
        next.clear();
        p = str;
        e = end;

        next.push_back( -1 );
        for( int i = 1; str[i] != end; ++i ) {
            int j = next[i - 1];
            while( j >= 0 && str[j + 1] != str[i] ) j = next[j];
            if( str[j + 1] == str[i] ) ++j;
            next.push_back( j );
        }
    }

    int find( const T* from, int startPos, int* nextCandidate ) {
        int len = 0;
        int pos = startPos;
       // while()
       return 0;
    }
private:
    static const int INVALID = INT_MIN;
    const T* p;
    const T e;
    std::vector< int > next;
};