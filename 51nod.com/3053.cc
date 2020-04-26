//
// Created by 关鑫 on 2020/4/24.
//

#include <stdio.h>
#include <stdint.h>
#include <vector>

#define MAXN 200001

int32_t dur[MAXN];
std::vector<int> son[MAXN];
bool vis[MAXN];
int32_t cost[MAXN];

int dfs(int x) {
    if( vis[x] ) return cost[x];
    vis[x] = true;
    if( son[x].empty() ) return cost[x] = dur[x];
    int32_t mt = 0;
    for( auto s : son[x] ) {
        int32_t tmp = dfs(s);
        if( tmp > mt ) mt = tmp;
    }
    return cost[x] = mt + dur[x];
}

int main() {

    int n, m;
    scanf("%d %d", &n, &m);
    for( int i = 1; i <= n; ++i ) scanf("%d", dur + i);

    int u, v;
    for( int i = 0; i < m; ++i ) {
        scanf("%d %d", &u, &v);
        son[v].push_back(u);
    }

    int32_t mt = 0;
    for( int i = 1; i <= n; ++i ) {
        int32_t tmp = dfs(i);
        if(tmp > mt) mt = tmp;
    }
    printf("%d\n", mt);

    return 0;
}