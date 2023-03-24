//
// Created by 关鑫 on 2022/2/7.
//

#include <cstdio>
#include <deque>

const int N = 100001;

int n;
int fa[N];
int wei[N];
std::deque<std::pair<int, int>> children[N];

void bfs(int n) {
    for (int i = 0; i < children[n].size(); ++i) {
        auto c = children[n][i].first;
        auto w = children[n][i].second;
        if (fa[c]) {
            children[n][i] = children[n].back();
            children[n].pop_back();
            --i;
            continue;
        }
        fa[c] = n;
        wei[c] = w;
    }
    for (auto pr : children[n]) bfs(pr.first);
}

int main() {

    int x, w;

    scanf("%d", &n);
    for (int i = 2; i <= n; ++i) {
        scanf("%d%d", &x, &w);
        children[i].emplace_back(x, w);
        children[x].emplace_back(i, w);
    }

    fa[1] = -1;
    bfs(1);



    return 0;
}