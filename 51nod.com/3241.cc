//
// Created by 关鑫 on 2022/1/29.
//

#include <stdio.h>
#include <algorithm>
#include <queue>

const int N = 100;

int timeCost[N];

int main() {

    int t;
    int n, m, x;
    int a, b;

    scanf("%d", &t);
    while(t--) {
        scanf("%d%d%d", &n, &m, &x);
        for(int i = 0; i < n; ++i) scanf("%d", timeCost + i);
        std::sort(timeCost, timeCost + n);
        if(m <= n) {
            a = std::upper_bound(timeCost, timeCost + n, x) - timeCost;
            b = m - a;
        }
        else {
            struct Pair {
                int end;
                int idx;

                Pair() {}
                Pair(int e, int i): end(e), idx(i) {}

                bool operator < (const Pair &other) const {
                    return end > other.end || (end == other.end && timeCost[idx] > timeCost[other.idx]);
                }
            };
            std::priority_queue<Pair> q;
            for(int i = 0; i < n; ++i) q.emplace(timeCost[i], i);
            m -= n;
            a = 0;
            while(m >= 0 && q.size() > 0) {
                Pair pr = q.top();
                if(pr.end > x) break;
                q.pop();
                ++a;
                if(pr.end < x && m > 0) {
                    q.emplace(pr.end + timeCost[pr.idx], pr.idx);
                    --m;
                }
            }
            b = q.size();
        }
        printf("%d %d\n", a, b);
    }

    return 0;
}
