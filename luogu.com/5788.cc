//
// Created by 关鑫 on 2022/7/11.
//

#include <cstdio>

const int N = 3000001;

int f[N];

struct Element {
    int idx;
    int val;
} stk[N];
int top = -1;

int main() {

    int n, x;
    scanf("%d", &n);

    stk[++top] = {0, int(1e9 + 5)};

    for (int i = 1; i <= n; ++i) {
        scanf("%d", &x);
        while (x > stk[top].val) {
            f[stk[top].idx] = i;
            --top;
        }
        stk[++top] = {i, x};
    }

    for (int i = 1; i <= n; ++i) {
        printf("%d ", f[i]);
    }

    return 0;
}