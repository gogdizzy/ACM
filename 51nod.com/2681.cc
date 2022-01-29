//
// Created by 关鑫 on 2021/5/10.
//

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 51;

char s[MAXN];
int dp[MAXN][MAXN];

int lcs(char* s1, int len1, char* s2, int len2) {
    for(int i = 0; i < len1; ++i) {
        for(int j = 0; j < len2; ++j) {
            dp[i+1][j+1] = s1[i] == s2[j] ? dp[i][j] + 1 : std::max(dp[i+1][j], dp[i][j+1]);
        }
    }
    return dp[len1][len2];
}

int main() {

    scanf("%s", s);
    int len = strlen(s);

    int lcsMax = 0;

    for(int i = 1; i < len - 1; ++i) {
        lcsMax = std::max(lcsMax, lcs(s, i, s + i, len - i));
    }

    printf("%d\n", len - lcsMax * 2);

    return 0;
}