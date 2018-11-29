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
    n[1] = 0;
    for( int i = 1; i < len; ++i ) {
        int j = n[i - 1];
        while( j >= 0 && s[j + 1] != s[i] ) j = n[j];
        if( s[j + 1] == s[i] ) ++j;
        n[i] = j;
    }
}