#include <stdio.h>

const int MAXS = 10002;
const int P = 998244353;

int dp[MAXS];
int presum[MAXS];

int main() {
    int n, L, R, s;
    for(s = 1; s < MAXS; ++s) dp[s] = presum[s] = 1;
    presum[0] = 1;
    scanf("%d", &n);
    while(n--) {
        scanf("%d%d", &L, &R);
        int sum = presum[L - 1];
        for(s = 0; s < L; ++s) dp[s] = presum[s] = 0;
        for(; s <= R; ++s) {
            dp[s] = sum;
            sum = presum[s];
            presum[s] = (dp[s] + presum[s - 1]) % P;
        }
        for(s = R + 1; s < MAXS; ++s) {
            dp[s] = 0;
            presum[s] = presum[R];
        }
        printf("===\n");
        for(s = 1; s < 10; ++s) printf("%d %d\n", dp[s], presum[s]);
    }
    printf("%d\n", presum[R]);
    return 0;
}
