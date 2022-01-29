//
// Created by 关鑫 on 2021/9/10.
//

#include <stdio.h>
#include <stdint.h>
#include <algorithm>

const int64_t INF = 1e18;
const int N = 2002;

struct Pr {
    int a, b;
} pr[N];

int64_t dp[2][N];

int main() {

    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d %d", &pr[i].a, &pr[i].b);

    std::sort(pr + 1, pr + n + 1, [](const Pr& x, const Pr& y) {
        return x.a > y.a;
    });

    for (int j = 0; j <= n + 1; ++j) dp[0][j] = dp[1][j] = -INF;
    int from = 0, to = 1;
    dp[from][1] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            dp[to][j] = std::max(dp[from][std::max(j - pr[i].a, 0) + 1] + pr[i].b, dp[from][j]);
        }
        from = to;
        to = 1 - to;
    }

    printf("%lld\n", std::max(0LL, *std::max_element(&dp[from][0], &dp[from][n])));

    return 0;
}