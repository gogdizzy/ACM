#include <cstdio>
#include <cstdint>

const int MAXN = 200000;

int64_t presum[MAXN + 2];

int main() {
    int n, x;
    scanf("%d", &n);
    for(int i = 2; i < n + 2; ++i) {
        scanf("%d", &x);
        presum[i] = presum[i - 2] + x;
    }
    
    int ans = 0;
    for(int i = 2; i < n + 2; ++i) {
        if((i ^ n) & 1) ans += (presum[i - 1] + presum[n + 1] - presum[i]) == (presum[i - 2] + presum[n] - presum[i - 1]);
        else ans += (presum[i - 1] + presum[n] - presum[i]) == (presum[i - 2] + presum[n + 1] - presum[i - 1]);
    }
    
    printf("%d\n", ans);
    return 0;
}
