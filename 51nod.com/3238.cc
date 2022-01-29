//
// Created by 关鑫 on 2020/12/23.
//

#include <cstdio>
#include <cstdint>
#include <map>
#include <algorithm>

const int MAXM = 100000;

struct Sushi {
    int start;
    int end;
    int value;
};

Sushi food[MAXM];

int main() {
    int m, x, t, s, p;
    scanf("%d%d", &m, &x);
    for(int i = 0; i < m; ++i) {
        scanf("%d%d%d", &t, &s, &p);
        food[i].start = t;
        food[i].end = t + s;
        food[i].value = p;
    }
    std::sort(food, food + m, [](const Sushi& a, const Sushi& b) {
        return a.end < b.end;
    });

    int64_t ans = 0;
    std::map<int, int64_t> dp;
    dp[0] = 0;
    for(int i = 0; i < m; ++i) {
        if(food[i].end > x) break;
        auto it = dp.upper_bound(food[i].start);
        --it;

        dp[food[i].end] = std::max(ans, it->second + food[i].value);
        ans = std::max(ans, dp[food[i].end]);
    }
    printf("%lld\n", ans);
    return 0;
}
