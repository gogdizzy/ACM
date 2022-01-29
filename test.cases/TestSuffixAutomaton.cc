//
// Created by 关鑫 on 2020/8/17.
//

#include <iostream>
#include <string>

#include "SuffixAutomaton.h"

struct MyState : public SuffixAutomaton< char, MyState >::StateBase {
    int trans[26];

    MyState( int slink, int maxlen ) : SuffixAutomaton< char, MyState >::StateBase( slink, maxlen ) {
        for( int i = 0; i < 26; ++i ) trans[i] = -1;
    }

    inline
    int GetTransition( char c ) { return trans[c - 'a']; }

    inline
    int SetTransition( char c, int x ) { return trans[c - 'a'] = x; }

    inline
    MyState Clone() { return *this; }
};

void test() {

    std::string s( "aabbabd" );

    SuffixAutomaton< char, MyState > sam;

    sam.Expand( s.cbegin(), s.cend() );

    for( int i = 0; i < s.size(); ++i ) {
        assert( sam.IsSuffix( s.cbegin() + i, s.cend() ) );
    }
    assert( !sam.IsSuffix( s.cbegin(), s.cbegin() + 4 ) );
    for( int i = 0; i < s.size(); ++i ) {
        for( int j = i; j <= s.size(); ++j ) {
            assert( sam.IsSub( s.cbegin() + i, s.cbegin() + j ) );
        }
    }

    std::cout << sam.SubSize() << '\n';

}

int main() {

    test();

    return 0;
}

