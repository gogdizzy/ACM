//
// Created by 关鑫 on 2021/5/17.
//

#include <cstdio>
#include <cstdint>
#include <algorithm>

const int MAXN = 10000;

int A[MAXN];
int64_t B[MAXN];
int C[MAXN];

int main() {

    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%d", A + i);
        for(B[i] = 10; A[i] >= B[i]; B[i] *= 10);
        C[i] = i;
    }
    std::sort(C, C + n, [&](const int x, const int y) {
        return A[x] * B[y] + A[y] < A[y] * B[x] + A[x];
    });
    for(int i = 0; i < n; ++i) printf("%d", A[C[i]]);
    putchar('\n');

    return 0;
}