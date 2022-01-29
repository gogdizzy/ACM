//
// Created by 关鑫 on 2021/5/8.
//

#include <cstdio>
#include <cstdint>
#include <algorithm>

const int MAXN = 100000;

int beauty[MAXN * 2];
int idx[MAXN * 2];

struct State {
    int pos1;
    int pos2;
    int64_t dist1;
    int64_t dist2;

    void set(int p1, int p2, int64_t d1, int64_t d2) {
        pos1 = p1;
        pos2 = p2;
        dist1 = d1;
        dist2 = d2;
    }
};

int main() {

    int n;
    scanf("%d", &n);
    for(int i = 0; i < n * 2; ++i) {
        scanf("%d", beauty + i);
        idx[i] = i;
    }

    std::sort(idx, idx + n * 2, [](const int a, const int b) {
        return beauty[a] < beauty[b];
    });

    State dp[2];
    int cur = 0, nxt = 1;
    dp[cur].set(0, 0, 0, 0);
    for(int i = 0; i < n * 2;) {
        int p1 = idx[i++];
        int p2 = idx[i++];
        dp[nxt].set(p1, p2,
                    std::min(dp[cur].dist1 + abs(p1 - dp[cur].pos1) + abs(p2 - dp[cur].pos2),
                             dp[cur].dist2 + abs(p1 - dp[cur].pos2) + abs(p2 - dp[cur].pos1)),
                    std::min(dp[cur].dist1 + abs(p2 - dp[cur].pos1) + abs(p1 - dp[cur].pos2),
                             dp[cur].dist2 + abs(p2 - dp[cur].pos2) + abs(p1 - dp[cur].pos1)));
        cur = nxt;
        nxt = 1 - cur;
    }

    printf("%lld\n", std::min(dp[cur].dist1, dp[cur].dist2));

    return 0;
}