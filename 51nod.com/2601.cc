//
// Created by 关鑫 on 2021/9/30.
//

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <vector>
#include <unordered_map>

const int N = 100002;
const int P = 1e9 + 7;
const int BASE = 131;

int8_t a[N];
int8_t b[N];
int PowMod[N];

void init(int n) {
    PowMod[0] = 1;
    for (int i = 1; i <= n; ++i) {
        PowMod[i] = (int64_t)PowMod[i - 1] * BASE % P;
    }
}

struct BaseHash {
    BaseHash(int b, int m) : base(b), mod(m) {
        h.push_back(0);
    }

    void update(int x) {
        h.push_back((h.back() * (int64_t)base + x) % mod);
    }

    // [l, r]
    int getHash(int l, int r) {
        return ((h[r] - h[l - 1] * (int64_t)PowMod[r - l + 1]) % mod + mod) % mod;
    }

    std::vector<int> h;
    int base;
    int mod;
};

BaseHash biu(BASE, P);
BaseHash piu(BASE, P);

bool check(int n, int len) {
    std::unordered_map<int64_t, int> uniq;
    for (int r = len; r <= n; ++r) {
        uniq[biu.getHash(r - len + 1, r)] = r;
    }
    for (int r = len; r <= n; ++r) {
        auto it = uniq.find(piu.getHash(r - len + 1, r));
        if (it != uniq.end() && memcmp(a + it->second - len + 1, b + r - len + 1, len) == 0) {
            return true;
        }
    }
    return false;
}


int main() {
freopen("/Users/guanxin/in.txt", "rt", stdin);
    int n, x;

    scanf("%d", &n);
    init(n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
        biu.update(a[i]);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", b + i);
        piu.update(b[i]);
    }

    int ans;
    int l = 1, r = n + 1;
    while (l < r) {
        int m = l + (r - l >> 1);
        if (check(n, m)) ans = m, l = m + 1;
        else r = m;
    }

    printf("%d\n", ans);

    return 0;
}