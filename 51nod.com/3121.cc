//
// Created by 关鑫 on 2021/9/29.
//

#include <stdio.h>
#include <stdint.h>
#include <string.h>

const int N = 200000;

int a[N], b[N];

int64_t mergeSort(int l, int r) {
    if (l + 1 >= r) return 0;
    int m = l + (r - l >> 1);
    int rv = mergeSort(l, m) + mergeSort(m, r);
    int p = l, q = m, t = l;
    while (t < r) {
        if (q >= r || (p < m && a[p] <= a[q])) b[t++] = a[p++];
        else {
            rv += m - p;
            b[t++] = a[q++];
        }
    }
    memcpy(a + l, b + l, sizeof(a[0]) * (r - l));
    return rv;
}

int main() {

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", a + i);

    printf("%lld\n", mergeSort(0, n));

    return 0;
}