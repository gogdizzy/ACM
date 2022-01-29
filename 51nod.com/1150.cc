//
// Created by 关鑫 on 2021/9/14.
//

// https://blog.csdn.net/alan_cty/article/details/53838015

#include <stdio.h>
#include <stdint.h>

const int BIT_WIDTH = 61;
const uint64_t MAX10 = 1e18;
const uint64_t MAX2 = (1ULL << BIT_WIDTH) - 1;
const int N = 50000;
const int M = N * BIT_WIDTH + 1;

uint64_t mask[BIT_WIDTH];
uint64_t a[N];
int tot = 0;
int trie[M][2];
int cnt[M];

void insert(uint64_t v) {
    int curNode = 0;
    for (int i = BIT_WIDTH - 1; i >= 0; --i) {
        int bit = (v & mask[i]) > 0;
        if (!trie[curNode][bit]) trie[curNode][bit] = ++tot;
        curNode = trie[curNode][bit];
        ++cnt[curNode];
    }
}

int calc(uint64_t v, uint64_t p10) {
    int rv = 0;
    int curNode = 0;
    for (int i = BIT_WIDTH - 1; i >= 0; --i) {
        int bit = (v & mask[i]) > 0;
        int bit2 = (p10 & mask[i]) > 0;
        if (bit2) rv += cnt[trie[curNode][bit]];
        curNode = trie[curNode][bit ^ bit2];
        if (!curNode) break;
    }
    return rv + cnt[curNode];
}

int main() {

    for (int i = 0; i < BIT_WIDTH; ++i) mask[i] = (1ULL << i);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%llu", a + i);
        insert(a[i]);
    }

    uint64_t ans = 0;
    uint64_t l = 10, r = 99;
    for (uint64_t j = 1; j <= 18; ++j) {
        for (int i = 0; i < n; ++i) {
            ans += j * (calc(a[i], r) - calc(a[i], l - 1));
        }
        l = r + 1;
        r = l * 10 - 1;
        // 因为数字不超过 1e18，它有 60 bit，两个数字的异或结果不会超过 60 bit
        // 必须保证二进制不超过61位，因为我们访问 trie 的时候是从高位到低位
        if (l >= MAX10) r = MAX2;
    }
    printf("%llu\n", ans);

    return 0;
}