//
// Created by 关鑫 on 2021/9/13.
//

#include <stdio.h>

#define LOWBIT(x) (x & -x)

int ans = 0;
int n;
int all;

void dfs(int vert, int l45, int r45) {
    if (vert == all) {
        ++ans;
        return;
    }
    int mask = all ^ (vert | l45 | r45);
    for (int bit = LOWBIT(mask); bit != 0; bit = LOWBIT(mask)) {
        dfs(vert | bit, ((l45 | bit) << 1) & all, (r45 | bit) >> 1);
        mask -= bit;
    }
}

int main() {

    scanf("%d", &n);
    all = (1 << n) - 1;
    for (int pos0 = 0; pos0 < n / 2; ++pos0) {
        int bit = (1 << pos0);
        dfs(bit, (bit << 1) & all, bit >> 1);
    }
    ans *= 2;
    if (n & 1) {
        int bit = 1 << (n / 2);
        dfs(bit, (bit << 1) & all, bit >> 1);
    }
    printf("%d\n", ans);

    return 0;
}