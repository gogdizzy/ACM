#include <cstdio>
#include <unordered_map>

const int MAXN = 30001;

int A[MAXN];

int main() {
    int n, x, S, sum = 0;
    int ans = 0;
    
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) scanf("%d", A + i);
    scanf("%d", &S);
    
    std::unordered_map<int, int> count;
    count[0] = 1;
    for(int i = 0; i < n; ++i) {
        sum += A[i];
        ans += count[sum - S];
        ++count[sum];
    }

    printf("%d\n", ans);
    return 0;
}
