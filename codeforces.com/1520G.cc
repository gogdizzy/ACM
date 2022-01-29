//
// Created by 关鑫 on 2021/6/17.
//

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <queue>
#include <vector>

const int POP_OVER = -2;
const int WALL = -1;
const int N = 2000;
const int M = 2000;
const short DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int map[N+2][M+2];
int64_t minCost[N+2][M+2];

struct Point {
    short x;
    short y;
};

struct Node {
    short x;
    short y;
    int64_t cost;

    bool operator<(const Node& other ) const {
        return cost > other.cost;
    }
};

int main() {
    // freopen("/Users/guanxin/in.txt", "rt", stdin);

    memset(map, -1, sizeof(map));
    memset(minCost, 0x7F, sizeof(minCost));

    int n, m, w;

    bool VIRTUAL_NODE_POP_OVER = false;
    int64_t VIRTUAL_NODE_MIN_COST = 0x7F7F7F7F7F7F7F7F;
    std::vector<Point> VIRTUAL_NODE_NEIBOUR;

    scanf("%d%d%d", &n, &m, &w);
    for(short r = 1; r <= n; ++r) {
        for(short c = 1; c <= m; ++c) {
            scanf("%d", &map[r][c]);
            if(map[r][c] > 0) VIRTUAL_NODE_NEIBOUR.push_back({c, r});
        }
    }

    std::priority_queue<Node> pq;
    minCost[1][1] = 0;
    pq.push({1, 1, 0});

    bool reach = false;
    while(!pq.empty()) {
        auto node = pq.top();
        pq.pop();
        if(node.x == m && node.y == n) {
            reach = true;
            break;
        }
        if(node.x < 0) {
            if(VIRTUAL_NODE_MIN_COST == node.cost) {
                VIRTUAL_NODE_POP_OVER = true;
                for(auto nb : VIRTUAL_NODE_NEIBOUR) {
                    if(minCost[nb.y][nb.x] != POP_OVER) {
                        auto tmp = VIRTUAL_NODE_MIN_COST + map[nb.y][nb.x];
                        if(tmp < minCost[nb.y][nb.x]) {
                            minCost[nb.y][nb.x] = tmp;
                            pq.push({nb.x, nb.y, tmp});
                        }
                    }
                }
            }
        }
        else if(minCost[node.y][node.x] == node.cost) {
            minCost[node.y][node.x] = POP_OVER;
            for(int i = 0; i < 4; ++i) {
                short x = node.x + DIR[i][0];
                short y = node.y + DIR[i][1];
                if(minCost[y][x] == POP_OVER || map[y][x] == WALL) continue;
                auto tmp = node.cost + w;
                if(tmp < minCost[y][x]) {
                    minCost[y][x] = tmp;
                    pq.push({x, y, tmp});
                }
            }
            if(map[node.y][node.x] > 0 && !VIRTUAL_NODE_POP_OVER) {
                auto tmp = node.cost + map[node.y][node.x];
                if(tmp < VIRTUAL_NODE_MIN_COST) {
                    VIRTUAL_NODE_MIN_COST = tmp;
                    pq.push({-1, -1, tmp});
                }
            }
        }
    }
    printf("%lld\n", reach ? minCost[n][m] : -1LL);

    return 0;
}