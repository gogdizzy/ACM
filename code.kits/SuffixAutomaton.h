//
// Created by 关鑫 on 2018-11-29.
//
//
//struct MyState : public SuffixAutomaton< char >::StateBase {
//    int trans[26];
//
//    MyState( int slink, int maxlen ) : SuffixAutomaton::StateBase( slink, maxlen ) {
//        for( int i = 0; i < 26; ++i ) trans[i] = -1;
//    }
//
//    inline
//    int GetTransition( char c ) { return trans[c - 'a']; }
//
//    inline
//    int SetTransition( char c, int x ) { return trans[c - 'a'] = x; }
//
//    inline
//    MyState Clone() { return *this; }
//};

#pragma once

#include <vector>

template < typename T, typename StateOfT >
class SuffixAutomaton {

public:
    struct StateBase {
        int slink;
        int maxlen;

        StateBase() : slink( -1 ), maxlen( 0 ) {}

        StateBase( int slink, int maxlen ) : slink( slink ), maxlen( maxlen ) {}
    };

    SuffixAutomaton() {
        _last = NewState( 0 );
    }

    SuffixAutomaton( size_t maxsize ) {
        _states.reserve( maxsize );
        _last = NewState( 0 );
    }

    void Expand( const T &x ) {
        int p = _last;

        auto cur = _last = NewState( _states[_last].maxlen + 1 );

        for( ; p >= 0 && _states[p].GetTransition( x ) == -1; p = _states[p].slink ) {
            _states[p].SetTransition( x, cur );
        }

        if( p == -1 ) {
            _states[cur].slink = 0;
            return;
        }

        int next = _states[p].GetTransition( x );
        if( _states[p].maxlen + 1 == _states[next].maxlen ) {
            _states[cur].slink = next;
            return;
        }

        auto clone = CloneState( next );
        _states[clone].maxlen = _states[p].maxlen + 1;
        _states[next].slink = _states[cur].slink = clone;

        for( ; p >= 0 && _states[p].GetTransition( x ) == next; p = _states[p].slink ) {
            _states[p].SetTransition( x, clone );
        }
    }

    template< typename Iter >
    void Expand( Iter beg, Iter end ) {
        for( ; beg != end; ++beg ) {
            Expand( *beg );
        }
    }

    template< typename Iter >
    bool IsSuffix( Iter beg, Iter end ) {
        int next = 0;
        auto cur = _states[next];
        for( ; beg != end; ++beg ) {
            next = cur.GetTransition( *beg );
            if( next < 0 ) return false;
            cur = _states[next];
        }
        return next == _last;
    }

    template< typename Iter >
    bool IsSub( Iter beg, Iter end ) {
        int next = 0;
        auto cur = _states[next];
        for( ; beg != end; ++beg ) {
            next = cur.GetTransition( *beg );
            if( next < 0 ) return false;
            cur = _states[next];
        }
        return true;
    }

    inline
    StateOfT& Get( int i ) {
        return _states[i];
    }

    inline
    size_t SubInState( int x ) {
        const auto &cur = _states[x];
        return cur.maxlen - _states[cur.slink].maxlen;
    }

    inline
    size_t SubSize() {
        size_t ret = 0;
        for( int i = 1; i < _states.size(); ++i ) {
            ret += SubInState( i );
        }
        return ret;
    }

    inline
    size_t Size() {
        return _states.size();
    }

protected:
    int NewState( int maxlen ) {
        _states.push_back( StateOfT( -1, maxlen ) );
        return _states.size() - 1;
    }

    int CloneState( int origin ) {
        _states.push_back( _states[origin].Clone() );
        return _states.size() - 1;
    }

private:
    std::vector< StateOfT > _states;
    int _last;
};