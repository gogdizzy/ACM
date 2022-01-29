//
// Created by 关鑫 on 2021/6/11.
//

#include <stdio.h>
#include <string.h>
#include <stdint.h>

const int P = 1000000007;
const int MAXL = 500;

char forest[MAXL][MAXL + 1];
int dp[MAXL][MAXL];

int calc(int r1, int c1, int r2, int c2) {

}

int main() {
    memset(dp, -1, sizeof(dp));
    int n, m;
    for(int r = 0; r < n; ++r) {
        scanf("%s", forest[r]);
    }
    printf("%d\n", calc(0, 0, n - 1, m - 1));
    return 0;
}