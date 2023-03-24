
#include <cstdio>
#include <cstdint>

struct Stat {
    int64_t count;
    int64_t sum;
};

const int64_t P = 1e9 + 7;
const int D_LEN = 19;
const int K_MAX = 100;
const int K_MIN = -100;


Stat dp[20][10][201];

void init() {

    for (int x = 0; x <= 9; ++x) {
        dp[0][x][x-K_MIN] = {1, x % P};
    }

    for (int d = 0; d < D_LEN; ++d) {
        for (int x = 0; x <= 9; ++x) {
            for (int k = K_MIN; k <= K_MAX; ++k) {
                for (int z = 0; z <= 9; ++z) {
                    int nk = z - k;
                    if (nk < K_MIN || nk > K_MAX) continue;
                    dp[d+1][z][nk-K_MIN].count += dp[d][x][k-K_MIN].count;
                    dp[d+1][z][nk-K_MIN].sum = (dp[d+1][z][nk-K_MIN].sum + dp[d][x][k-K_MIN].sum) % P;
                }
            }
        }
    }
}

int64_t calc(int64_t r, int32_t k) {
printf("calc %lld %d\n", r, k);
    int64_t r0 = r;
    int digit[21];
    int size = 0;
    if (r == 0) {
        digit[size++] = 0;
    }
    while (r) {
        digit[size++] = r % 10;
        r /= 10;
    }

    int64_t rv = 0;
    int32_t presum = 0;
    for (int pos = size - 1, sign = 1; pos >= 0; --pos, sign = -sign) {
        for (int x = 0; x < digit[pos]; ++x) {
            int32_t needK = (k - presum) * sign;
            if (needK < K_MIN || needK > K_MAX) continue;
            rv = (rv + dp[pos][x][needK-K_MIN].sum) % P;
printf("add %d %d %d %lld\n", pos, x, needK - K_MIN, dp[pos][x][needK-K_MIN].sum);
        }
        presum += digit[pos] * sign;
    }
    if (presum == k) rv = (rv + r0) % P;
    return rv;
}


int main() {
    int64_t l, r;
    int32_t k;
    init();
    scanf("%lld%lld%d", &l, &r, &k);
    printf("%lld\n", (calc(r, k) - calc(l - 1, k) + P) % P);

    return 0;
}
