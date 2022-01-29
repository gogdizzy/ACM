//
// Created by 关鑫 on 2022/1/29.
//

#ifdef VER1

#include <cstdio>
#include <algorithm>

const int N = 1000 + 2;
const int M = 1000 + 2;

int h[N][M];
int v[N][M];
int n, m;

bool isPeak(int y, int x) {
    return h[y][x] >= h[y-1][x] &&
           h[y][x] >= h[y][x-1] &&
           h[y][x] >= h[y][x+1] &&
           h[y][x] >= h[y+1][x];
}

void bfs(int y, int x) {
    if (y - 1 > 0) {
        if (h[y][x] > h[y-1][x]) {
            v[y-1][x] = std::max(v[y-1][x], v[y][x] + 1);
            bfs(y - 1, x);
        }
    }
    if (x - 1 > 0) {
        if (h[y][x] > h[y][x-1]) {
            v[y][x-1] = std::max(v[y][x-1], v[y][x] + 1);
            bfs(y, x - 1);
        }
    }
    if (x + 1 <= m) {
        if (h[y][x] > h[y][x+1]) {
            v[y][x+1] = std::max(v[y][x+1], v[y][x] + 1);
            bfs(y, x + 1);
        }
    }
    if (y + 1 <= n) {
        if (h[y][x] > h[y+1][x]) {
            v[y+1][x] = std::max(v[y+1][x], v[y][x] + 1);
            bfs(y + 1, x);
        }
    }
}

int main() {

    scanf("%d%d", &n, &m);
    for (int y = 1; y <= n; ++y) {
        for (int x = 1; x <= m; ++x) scanf("%d", &h[y][x]);
    }
    for (int y = 1; y <= n; ++y) {
        for (int x = 1; x <= m; ++x) {
            if ( isPeak(y, x)) {
                v[y][x] = 1;
                bfs(y, x);
            }
        }
    }

    int ans = 0;
    for (int y = 1; y <= n; ++y) {
        for (int x = 1; x <= m; ++x) ans = std::max(ans, v[y][x]);
    }

    printf("%d\n", ans);
    return 0;
}

#endif

#include <cstdio>
#include <algorithm>

const int N = 1000 + 2;
const int M = 1000 + 2;
const int DIR[][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

int h[N][M];
int v[N][M];
int n, m;

int dp(int y, int x) {
    if (v[y][x]) return v[y][x];
    v[y][x] = 1;
    for (int i = 0; i < 4; ++i) {
        int ny = y + DIR[i][0];
        int nx = x + DIR[i][1];
        if (1 <= ny && ny <= n && 1 <= nx && nx <= m && h[ny][nx] > h[y][x]) {
            v[y][x] = std::max(v[y][x], dp(ny, nx) + 1);
        }
    }
    return v[y][x];
}

int main() {

    scanf("%d%d", &n, &m);
    for (int y = 1; y <= n; ++y) {
        for (int x = 1; x <= m; ++x) scanf("%d", &h[y][x]);
    }
    int ans = 0;
    for (int y = 1; y <= n; ++y) {
        for (int x = 1; x <= m; ++x) ans = std::max(ans, dp(y, x));
    }

    printf("%d\n", ans);
    return 0;
}