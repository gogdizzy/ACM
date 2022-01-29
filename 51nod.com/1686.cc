//
// Created by 关鑫 on 2021/9/22.
//

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unordered_map>

const int N = 100001;

int a[N];
int pre[N];
int next[N];

void linkSame(int n) {
    std::unordered_map<int, int> lastPos;
    for (int i = 1; i <= n; ++i) {
        auto it = lastPos.find(a[i]);
        if (it != lastPos.end()) next[it->second] = i;
        lastPos[a[i]] = i;
    }
}

int64_t calc(int x, int n) {
    memset(pre, 0, sizeof(pre[0]) * n);
    for (int i = 1; i <= n; ++i) {
        if (pre[i] != 0) continue;
        int windowL = i, windowR = i;
        for (int k = 0; k < x - 1; ++k) {
            if (next[windowR] > 0) {
                pre[windowR] = -1;
                windowR = next[windowR];
            }
            else {
                pre[windowR] = -1;
                windowR = 0;
                break;
            }
        }
        while (windowR > 0) {
            pre[windowR] = windowL;
            windowL = next[windowL];
            windowR = next[windowR];
        }
    }

    int64_t rv = 0;
    for (int l = 0, r = 1; r <= n; ++r) {
        l = std::max(l, pre[r]);
        rv += l;
    }
    return rv;
}

int main() {

    int64_t n, k;
    scanf("%lld%lld", &n, &k);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    linkSame(n);

    int L = 1, R = n + 1;
    while (L < R - 1) {
        int M = (L + R) / 2;
        if (calc(M, n) >= k) L = M;
        else R = M;
    }
    printf("%d\n", L);
    return 0;
}

// code from remoon

//#include <cstdio>
//#include <cstring>
//#include <algorithm>
//#define sid 200050
//#define ri register int
//#define ll long long
//using namespace std;
//
//char RR[23456];
//inline char gc() {
//    static char *S = RR + 23333, *T = RR + 23333;
//    if(S == T) S = RR, fread(RR, 1, 23333, stdin);
//    return *S ++;
//}
//template <typename re>
//inline re read(re op) {
//    re p = 0, w = 1; char c = gc();
//    while(c > '9' || c < '0') { if(c == '-') w = -1; c = gc(); }
//    while(c >= '0' && c <= '9') { p = p * 10 + c - '0'; c = gc(); }
//    return p * w;
//}
//
//ll k;
//int n, cnt;
//int vis[sid], a[sid], H[sid];
//
//bool ck(int mid) {
//    memset(vis, 0, sizeof(vis));
//    ri l = 1, ex = 0; ll num = 0;
//    for(ri r = 1; r <= n; r ++) {
//        vis[a[r]] ++;
//        while(vis[a[r]] >= mid) {
//            num += (n - r + 1);
//            vis[a[l ++]] --;
//        }
//    }
//    return num >= k;
//}
//
//int main() {
//    n = read(1); k = read(1ll);
//    for(ri i = 1; i <= n; i ++) H[i] = a[i] = read(1);
//    sort(H + 1, H + n + 1);
//    cnt = unique(H + 1, H + n + 1) - H - 1;
//    for(ri i = 1; i <= n; i ++) a[i] = lower_bound(H + 1, H + cnt + 1, a[i]) - H;
//    int l = 1, r = n, ans = -1;
//    while(l <= r) {
//        int mid = (l + r) >> 1;
//        if(ck(mid)) l = mid + 1, ans = mid;
//        else r = mid - 1;
//    }
//    printf("%d\n", ans);
//    return 0;
//}