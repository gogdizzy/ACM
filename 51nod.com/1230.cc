//
// Created by 关鑫 on 2021/4/20.
//
// 参考：https://blog.csdn.net/f_zyj/article/details/73252188

#include <stdio.h>
#include <stdint.h>
#include <string.h>

const int MAXP = 1540;
const int MAXD = 20;
const int MAXS = 163;
const int MAXS2 = 1459;

bool prime[MAXP];
int64_t dp[MAXD][MAXS][MAXS2];
int digit[MAXD];

void init() {
    memset(dp, -1, sizeof(dp));
    memset(prime, 1, sizeof(prime));
    prime[0] = prime[1] = false;
    for(int i = 2; i < MAXP; ++i) {
        if(prime[i]) {
            for(int j = i * i; j < MAXP; j += i) {
                prime[j] = false;
            }
        }
    }
}

int64_t dfs(int curPos, int sum, int sqrSum, bool flag) {
    if(curPos == -1) return prime[sum] && prime[sqrSum] ? 1 : 0;
    if(!flag && dp[curPos][sum][sqrSum] != -1) return dp[curPos][sum][sqrSum];
    int64_t ret = 0;
    int lim = flag ? digit[curPos] : 9;
    for(int d = 0; d <= lim; ++d) {
        ret += dfs(curPos - 1, sum + d, sqrSum + d * d, flag && (d == lim));
    }
    if(!flag) {
        dp[curPos][sum][sqrSum] = ret;
    }
    return ret;
}

int64_t solve(int64_t x) {
    int len = 0;
    while(x) {
        digit[len++] = x % 10;
        x /= 10;
    }
    return dfs(len - 1, 0, 0, true);
}



int main() {
    init();
    int n;
    int64_t x, y;

    scanf("%d", &n);
    while(n--) {
        scanf("%lld%lld", &x, &y);
        printf("%lld\n", solve(y) - solve(x - 1));
    }
    return 0;
}