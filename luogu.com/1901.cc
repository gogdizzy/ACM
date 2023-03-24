//
// Created by 关鑫 on 2022/7/11.
//

#include <cstdio>
#include <cstdint>

const int N = 1e6 + 1;

int32_t sum[N];

struct Element {
    int idx;
    int h;
    int v;
} stk[N];

int top = -1;

int main() {

    int n, h, v, lv;
    scanf("%d", &n);

    stk[++top] = {0, int(2e9 + 10), 0};

    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &h, &v);
        while (h > stk[top].h) sum[i] += stk[top--].v;
        lv = 0;
        if (h == stk[top].h) lv = stk[top--].v;
        sum[stk[top].idx] += v;
        stk[++top] = {i, h, v + lv};
    }

    int ans = sum[1];
    for (int i = 2; i <= n; ++i)
        if (sum[i] > ans) ans = sum[i];

    printf("%d\n", ans);

    return 0;
}