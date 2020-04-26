//
// Created by 关鑫 on 2020/4/26.
//

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <queue>

#define MAXN 100000

class PrimeTable {

public:
    PrimeTable( int maxn ) {
        maxn_ = maxn;
        if( maxn_ < 10 ) maxn_ = 10;
        pmcount_ = static_cast< int >( 1.25506 * maxn_ / log( maxn_ ) + 1 );
        bits_ = new uint64_t[maxn_/64+1];
        primes_ = new uint32_t[pmcount_];
        pcount_ = 0;
        memset( bits_, 0, sizeof( uint64_t ) * (maxn_/64+1) );

        uint32_t  rt = (uint32_t)sqrt( (double)maxn_ ) + 1;

        for( uint32_t i = 2; i <= maxn_; ++i ) {
            if( !test_bit( i ) ) {
                primes_[pcount_++] = i;
                if( i < rt ) {
                    for( uint32_t j = i * i; j <= maxn_; j += i ) {
                        set_bit( j );
                    }
                }
            }
        }
    }
    ~PrimeTable() {
        if( bits_ ) { delete[] bits_; bits_ = nullptr; }
        if( primes_ ) { delete[] primes_; primes_ = nullptr; }
    }

    inline
    bool is_prime( int x ) { return !test_bit( x ); }

    inline
    uint32_t* begin() { return primes_; }

    inline
    uint32_t* end() { return primes_ + pcount_; }

protected:
    inline
    bool test_bit( uint32_t i ) {
        return bits_[i>>6] & (1ULL << (i & 63));
    }

    inline
    void set_bit( uint32_t i ) {
        bits_[i>>6] |= (1ULL << (i & 63));
    }

private:
    int maxn_;
    int pcount_;
    int pmcount_;
    uint64_t *bits_;
    uint32_t *primes_;
};

PrimeTable ptable(MAXN);
bool vis[MAXN];
int step[MAXN];
const int tens[] = { 10000, 1000, 100, 10, 1 };

void split( int from, int *digit ) {

    const int *ptens = from >= 10000 ? tens : tens + 1;
    int pos = 0;
    while( from > 0 ) {
        digit[pos] = from / ptens[pos];
        from %= ptens[pos];
        ++pos;
    }
}

int bfs(int from, int to) {

    if( from == to ) return 0;

    const int LEN = from >= 10000 ? 5 : 4;
    const int *ptens = from >= 10000 ? tens : tens + 1;

    memset( vis, 0, sizeof(vis) );
    step[from] = 0;
    vis[from] = true;
    std::queue< int > Q;
    Q.push( from );

    while( Q.size() ) {
        int cur = Q.front();
        Q.pop();
        int digit[5] = { 0 };
        split( cur, digit );

        for( int pos = 0; pos < LEN; ++pos ) {
            int tmp = cur - digit[pos] * ptens[pos];
            for( int i = !pos; i < 10; ++i ) {
                int tmp2 = tmp + ptens[pos] * i;
                if( tmp2 == to ) return step[cur] + 1;
                if( !vis[tmp2] && ptable.is_prime(tmp2) ) {
                    Q.push( tmp2 );
                    step[tmp2] = step[cur] + 1;
                    vis[tmp2] = true;
                }
            }
        }
    }

    return -1;
}

int main() {
    int n, A, B;
    scanf( "%d", &n );
    while( n-- ) {
        scanf( "%d %d", &A, &B );
        int ret = bfs( A, B );
        if( ret < 0 ) puts( "No solution" );
        else printf( "%d\n", ret );
    }

    return 0;
}