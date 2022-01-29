//
// Created by 关鑫 on 2021/9/3.
//

#include <stdio.h>

const int N = 20;

int p[N];
double sum[N];

int bit1Count(int x) {
    int ans = 0;
    while(x) {
        ++ans;
        x &= (x - 1);
    }
    return ans;
}

int main() {

    int n, r;
    scanf("%d%d", &n, &r);
    for (int i = 0; i < n; ++i) scanf("%d", p + i);

    double total = 0.0;
    for (int m = 0; m < (1 << n); ++m) {
        if (bit1Count(m) == r) {
            double prop = 1.0;
            for (int i = 0; i < n; ++i) {
                prop *= (m & (1 << i)) ? p[i] : (100 - p[i]);
            }
            for (int i = 0; i < n; ++i) {
                if (m & (1 << i)) sum[i] += prop;
            }
            total += prop;
        }
    }
    for (int i = 0; i < n; ++i) {
        printf("%f ", sum[i] / total);
    }

    return 0;
}

