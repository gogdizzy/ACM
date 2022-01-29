//
// Created by 关鑫 on 2020/4/28.
//

#include <cstdio>
#include <vector>
#include <set>

const int N = 100001;
const int M = 100001;

int cost[N];
struct Merge {int a, b, c;} merge[M];
std::vector<int> father[N];
std::vector<int> way[N];

struct Cmp {
    bool operator ()(const int x, const int y) const {
        return cost[x] < cost[y] || (cost[x] == cost[y] && x < y);
    }
};

int main() {
    int n, m, a, b, c;
    std::set<int, Cmp> s;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", cost + i);
        s.insert(i);
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d%d", &a, &b, &c);
        merge[i] = {a, b, c};
        father[a].push_back(c);
        father[b].push_back(c);
        way[c].push_back(i);
    }

    while (s.size()) {
        int minV = *s.begin();
        s.erase(s.begin());
        bool shrink = false;
        for (auto i : way[minV]) {
            auto& m = merge[i];
            auto co = cost[m.a] + cost[m.b];
            if (co < cost[minV]) {
                shrink = true;
                cost[minV] = co;
            }
        }
        if (shrink) {
            for (auto i : father[minV]) {
                s.insert(i);
            }
        }
    }

    for (int i = 1; i <= n; ++i) printf("%d ", cost[i]);
    return 0;
}
