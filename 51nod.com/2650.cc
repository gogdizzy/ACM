//
// Created by 关鑫 on 2022/2/21.
//

#include <cstdio>
#include <cstdint>
#include <vector>
#include <queue>

const int N = 501;

std::vector<std::pair<int, int>> e[N * 2];
bool vis[N * 2];
int64_t minCost[N * 2];

int64_t dijkstra(int s, int t) {

    for (int i = 0; i < N * 2; ++i) minCost[i] = std::numeric_limits<int64_t>::max();

    struct Node {
        int v;
        int64_t cost;
        Node() {}
        Node(int v0, int64_t c0) : v(v0), cost(c0) {}
    };

    struct Cmp {
        bool operator()(const Node& x, const Node& y) const {
            return x.cost > y.cost;
        }
    };

    std::priority_queue<Node, std::vector<Node>, Cmp> q;
    q.emplace(s, 0);
    minCost[s] = 0;
    while (!q.empty()) {
        auto cur = q.top();
        q.pop();

        printf("cur %d %lld\n", cur.v, cur.cost);

        if (cur.v == t) return cur.cost;
        if (cur.cost != minCost[cur.v]) continue;
        vis[cur.v] = true;

        for (auto& pr : e[cur.v]) {
            auto nb = pr.first;
            auto dis = pr.second;
            if (vis[nb]) continue;
            auto newCost = cur.cost + dis;
            if (newCost >= minCost[nb]) continue;
            printf("  push %d %lld\n", nb, newCost);
            minCost[nb] = newCost;
            q.emplace(nb, newCost);
        }
    }
    return -1;
}

int main() {
    int n, m;
    int u, v, w, u2, v2, w2;
    int s, t, t2;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        e[u].emplace_back(v, w);
        e[v].emplace_back(u, w);
        u2 = u + N;
        v2 = v + N;
        w2 = w / 2;
        e[u2].emplace_back(v2, w);
        e[v2].emplace_back(u2, w);
        e[u].emplace_back(v2, w2);
        e[v].emplace_back(u2, w2);
    }
    scanf("%d%d", &s, &t);
    t2 = t + N;
    printf("%lld\n", std::min(dijkstra(s, t), dijkstra(s, t2)));

    return 0;
}