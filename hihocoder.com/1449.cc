/**
 * http://hihocoder.com/problemset/problem/1449
 * 后缀自动机三·重复旋律6
 * 思路：后缀自动机，每条suffix-path上，累加子串的重复次数，例如一条path是8-6-3-0，则状态8里面的都出现1次，状态6里面的出现的次数要累加上8的次数
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

int cnt[MAXN<<1];
int rank[MAXN<<1];
int right[MAXN<<1];
int ans[MAXN<<1];

int main() {
    SuffixAutomaton sam;

    scanf( "%s", s );

    int len = 0;
    while( s[len] ) sam.expand( s[len++] - 'a' );

    // 统计每个长度有多少不同的子串
    for( int i = 0; i < sam.size(); ++i ) {
        ++cnt[sam.get(i).maxlen];
    }

    // maxlen大的cnt也大
    for( int i = 1; i <= len; ++i ) {
        cnt[i] += cnt[i - 1];
    }

    // state按照maxlen长度，从小到大排序，相同长度无所谓
    for( int i = 0; i < sam.size(); ++i ) {
        rank[--cnt[sam.get(i).maxlen]] = i;
    }

    // 标记绿点为1
    for( int i = 0, c = 0; i < len; ++i ) {
        ++right[c = sam.get(c).trans[s[i]-'a']];
    }

    // 倒序，优先碰到较长的
    for( int i = sam.size() - 1; i > 0; --i ) {
        int p = rank[i];
        auto& state = sam.get(p);
        right[state.slink] += right[p];
        if( right[p] > ans[state.maxlen] ) ans[state.maxlen] = right[p];
    }

    for( int i = len - 1; i > 0; --i ) {
        if( ans[i+1] > ans[i] ) ans[i] = ans[i+1];
    }

    for( int i = 1; i <= len; ++i ) {
        printf( "%d\n", ans[i] );
    }

    return 0;
}
