//
// Created by 关鑫 on 2022/1/27.
//

#include <cstdio>
#include <cstdint>
#include <algorithm>

const int64_t P = 1000000007;

int64_t countV(int64_t w, int64_t h) {
    return (w + 1) * (h + 1) % P;
}

int64_t countR(int64_t w, int64_t h) {
    return w * (w + 1) / 2 % P * (h * (h + 1) / 2 % P) % P;
}

int main() {
    int64_t m, n, u, v, s, t;
    scanf("%lld%lld%lld%lld%lld%lld", &m, &n, &u, &v, &s, &t);

    int64_t ans = (countR(m, n) -
                   countV(u - 1, v - 1) * countV(m - u, n - v) % P -
                   countV(s - 1, t - 1) * countV(m - s, n - t) % P +
                   countV(std::min(u, s) - 1, std::min(v, t) - 1) * countV(m - std::max(u, s), n - std::max(v, t)) % P + P + P) % P;
    printf("%lld\n", ans);

    return 0;
}