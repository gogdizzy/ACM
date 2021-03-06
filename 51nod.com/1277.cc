/**
 * http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1277
 * 字符串中的最大值
 * 思路：KMP 或 后缀自动机
 **/

#define VER2

#ifdef VER2

#include <stdio.h>
#include <vector>


#define MAXN 100001

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

int main() {
    SuffixAutomaton sam;
    long long ans = 0, tmp;

    scanf( "%s", s );

    int len = 0;
    while( s[len] ) sam.expand( s[len++] - 'a' );

    for( int i = 0; i < sam.size(); ++i ) {
        ++cnt[sam.get(i).maxlen];
    }

    for( int i = 1; i <= len; ++i ) {
        cnt[i] += cnt[i - 1];
    }

    for( int i = 0; i < sam.size(); ++i ) {
        rank[--cnt[sam.get(i).maxlen]] = i;
    }

    for( int i = 0, c = 0; i < len; ++i ) {
        ++right[c = sam.get(c).trans[s[i]-'a']];
    }

    for( int i = sam.size() - 1; i >= 0; --i ) {
        int p = rank[i];
        right[sam.get(p).slink] += right[p];
    }

    for( int i = 0, c = 0; i < len; ++i ) {
        tmp = (long long)right[c = sam.get(c).trans[s[i]-'a']] * (i + 1);
        if( tmp > ans ) ans = tmp;
    }

    printf( "%lld\n", ans );
    return 0;
}

#endif

#ifdef VER1

#include <stdio.h>
#include <string.h>

#define MAXN 100002

char s[MAXN];
int n[MAXN];
int rep[MAXN];

int main() {
	scanf( "%s", s + 1 );
	int len = strlen( s + 1 );
	long long ans = 0, tmp;

	// s[1..n[i]] is suffix of s[1..i]
	n[1] = 0;
	for( int i = 2; i <= len; ++i ) {
		int j = n[i - 1];
		while( j && s[j + 1] != s[i] ) j = n[j];
		if( s[j + 1] == s[i] ) ++j;
		n[i] = j;
	}

	for( int i = len; i > 0; --i ) {
		tmp = (long long)i * ++rep[i];
		if( tmp > ans ) ans = tmp;
		rep[n[i]] += rep[i];
	}

	printf( "%lld\n", ans );
	return 0;
}

#endif