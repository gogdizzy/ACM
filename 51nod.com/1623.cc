//
// Created by 关鑫 on 2021/3/24.
//

#include <cstdio>
#include <cstdint>

const int MASK_MAX = (1 << 10);
const int DIGIT_MAX = 10;
const int NUM_LENGTH = 20;

int nextMask[MASK_MAX][DIGIT_MAX];
int op[MASK_MAX][DIGIT_MAX];
int64_t f[NUM_LENGTH][MASK_MAX][NUM_LENGTH];
int bitCount[MASK_MAX];

int countBit( int x ) {
    int ans = 0;
    while( x ) {
        x &= ( x - 1 );
        ++ans;
    }
    return ans;
}

void init() {
    for( int i = 0; i < MASK_MAX; ++i ) {
        bitCount[i] = countBit( i ) - (i & 1);
        for( int j = 0; j < DIGIT_MAX; ++j ) {
            nextMask[i][j] = (i & ((1 << j) - 1) | (1 << j));
            op[i][j] = (j == 0 || (i & (1 << j))) ? 0 : 1;
        }
    }

    f[0][0][0] = 1;
    for( int i = 0; i < NUM_LENGTH - 1; ++i ) {
        for( int j = 0; j < MASK_MAX; ++j ) {
            for( int k = 0; k < NUM_LENGTH; ++k ) {
                for( int x = 0; x < DIGIT_MAX; ++x ) {
                    f[i+1][nextMask[j][x]][k+op[j][x]] += f[i][j][k];
                }
            }
        }
    }
}



void update( int & need_op, int & asc_mask, int digit ) {
    int dmask = (1 << (digit + 1)) - 1;
    need_op += bitCount[asc_mask & ~dmask];
    asc_mask &= dmask;
    asc_mask |= (1 << digit);
}

int64_t count( int64_t num, int64_t k ) {
    int digits[20];
    int num_len = 0;
    while( num ) {
        digits[num_len++] = num % 10;
        num /= 10;
    }
    if( num_len == 0 ) digits[num_len++] = 0;

    int64_t ans = 0;
    int need_op = 0;
    int asc_mask = 0;
    for( int pos = num_len - 1; pos >= 0; --pos ) {
        for( int d = 0; d < digits[pos]; ++d ) {
            int tmp_need_op = need_op;
            int tmp_asc_mask = asc_mask;
            update( tmp_need_op, tmp_asc_mask, d );
            for( int m = 0; m < MASK_MAX; ++m ) {
                int remain_k = k - tmp_need_op - bitCount[tmp_asc_mask & ~m];
                if( remain_k >= 0 ) {
                    ans += f[pos][m][remain_k];
                    if( f[pos][m][remain_k] ) printf( "pos: %d old_digit: %d mask: %d asc_mask: %d add: %d remain_k: %d\n", pos, d, m, tmp_asc_mask, f[pos][m][remain_k], remain_k );
                }
            }
        }
        update( need_op, asc_mask, digits[pos] );
        if( need_op + bitCount[asc_mask] > k ) break;
    }
    if( need_op + bitCount[asc_mask] == k ) ++ans;
    return ans;
}

int main() {

    init();

//    for( int i = 0; i < MASK_MAX; ++i ) {
//        if(f[1][i][1]) printf( "%d %d\n", i, f[1][i][1] );
//    }
    int64_t L, R, k;
    scanf( "%lld%lld%lld", &L, &R, &k );

    printf( "%lld\n", count( R, k ) - count( L - 1, k ) );

    printf( "f110 = %d\n", f[1][1][0] );
    printf( "f111 = %d\n", f[1][1][1] );

    return 0;
}