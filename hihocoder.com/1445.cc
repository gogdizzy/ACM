/**
 * http://hihocoder.com/problemset/problem/1445
 * 后缀自动机二·重复旋律5
 * 思路：后缀自动机，所有状态里面的字符串数量加和
 **/

#include <stdio.h>
#include <vector>

#define MAXN 1000001

char s[MAXN];

class SuffixAutomaton {

public:
    struct State {
        int slink;
        int maxlen;
        int trans[26];

        State() : slink( -1 ), maxlen( 0 ) {
            for( int i = 0; i < sizeof(trans) / sizeof(trans[0]); ++i ) {
                trans[i] = -1;
            }
        }

        State( int slink, int maxlen ) : slink( slink ), maxlen( maxlen ) {
            for( int i = 0; i < sizeof(trans) / sizeof(trans[0]); ++i ) {
                trans[i] = -1;
            }
        }

        State clone() {
            return *this;
        }
    };

    SuffixAutomaton() {
        last_ = new_state( 0 );
    }

    SuffixAutomaton( size_t maxsize ) : states_( maxsize ) {
        last_ = new_state( 0 );
    }

    void expand( int x ) {
        int p = last_;

        auto cur = last_ = new_state( states_[last_].maxlen + 1 );

        for( ; p >= 0 && states_[p].trans[x] == -1; p = states_[p].slink ) {
            states_[p].trans[x] = cur;
        }

        if( p == -1 ) {
            states_[cur].slink = 0;
            return;
        }

        int next = states_[p].trans[x];
        if( states_[p].maxlen + 1 == states_[next].maxlen ) {
            states_[cur].slink = next;
            return;
        }

        auto clone = clone_state( next );
        states_[clone].maxlen = states_[p].maxlen + 1;
        states_[next].slink = states_[cur].slink = clone;

        for( ; p >= 0 && states_[p].trans[x] == next; p = states_[p].slink ) {
            states_[p].trans[x] = clone;
        }
    }

    inline
    State& get( int i ) {
        return states_[i];
    }

    inline
    size_t size() {
        return states_.size();
    }

protected:
    int new_state( int maxlen ) {
        states_.push_back( State( -1, maxlen ) );
        return states_.size() - 1;
    }

    int clone_state( int origin ) {
        states_.push_back( states_[origin].clone() );
        return states_.size() - 1;
    }

private:
    std::vector< State > states_;
    int last_;
};

int main() {
    SuffixAutomaton sam;
    long long ans = 0;

    scanf( "%s", s );

    int len = 0;
    while( s[len] ) sam.expand( s[len++] - 'a' );

    for( int i = 1; i < sam.size(); ++i ) {
        auto& state = sam.get( i );
        ans += state.maxlen - sam.get( state.slink ).maxlen;
    }

    printf( "%lld\n", ans );
    return 0;
}
