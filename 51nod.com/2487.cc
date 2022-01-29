#include <stdio.h>

const int MAXN = 50002;

int ring[MAXN];
int dp[MAXN][2];

inline
int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n, ans = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) scanf("%d", ring + i);

    dp[1][0] = ring[0];
    dp[1][1] = 0;
    for(int i = 2; i < n - 1; ++i) {
        dp[i][0] = max(dp[i-1][0], dp[i-1][1]);
        dp[i][1] = dp[i-1][0] + ring[i];
    }
    ans = max(dp[n-2][0], dp[n-2][1]);

    dp[0][0] = 0;
    dp[0][1] = 0;
    for(int i = 1; i < n; ++i) {
        dp[i][0] = max(dp[i-1][0], dp[i-1][1]);
        dp[i][1] = dp[i-1][0] + ring[i];
    }
    ans = max(ans, max(dp[n-1][0], dp[n-1][1]));

    printf("%d\n", ans);
    return 0;
}
