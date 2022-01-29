#include <cstdio>
#include <algorithm>

const int MAXN = 20001;

char s[MAXN];

int main() {
    int n, zeroTotal = 0, zeroCur = 0;
    int ans = MAXN;
    scanf("%d%s", &n, s);
    for(int i = 0; s[i]; ++i) if(s[i] == '0') ++zeroTotal;
    for(int i = 0; i <= n; ++i) {
        ans = std::min(ans, (i - zeroCur) + (zeroTotal - zeroCur));
        if(s[i] == '0') ++zeroCur;
    }
    printf("%d\n", ans);
    return 0;
}
