//
// Created by 关鑫 on 2021/5/17.
//

#include <cstdio>
#include <cstdint>
#include <algorithm>

const int MAXN = 100000;

struct Person {
    int value;
    int time;
};

Person A[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%d%d", &A[i].value, &A[i].time);
    }
    std::sort(A, A + n, [&](const Person & x, const Person & y) {
        return x.value * y.time > y.value * x.time;
    });

for(int i = 0; i < n; ++i) {
    //if(A[i].time == 0) 
    printf("%d %d %d\n", i, A[i].value, A[i].time);
}


    int64_t ans = 0;
    int64_t waitTime = 0;
    for(int i = 0; i < n; ++i) {
        waitTime += A[i].time;
        ans += A[i].value * waitTime;
    }

    printf("%lld\n", ans);
    return 0;
}
