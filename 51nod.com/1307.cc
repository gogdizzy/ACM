//
// Created by 关鑫 on 2020/5/15.
//

// 参考 http://blog.csdn.net/fsss_7/article/details/50545374

#include <stdio.h>
#include <stdint.h>

#define MAXN 50000

struct rope_t {
    int32_t c;  // 容量
    int32_t w;  // 自重
    int32_t p;  // 父节点
    int64_t wt; // 当前子树总重
};

rope_t ropes[MAXN];

int father[MAXN];

int find( int i ) {
    if( father[i] == i ) return i;
    return father[i] = find( father[i] );
}

int update( int i, int ans ) {
    // 并查集是这样的，开始每个节点自己单独为一个集合
    // 检查到某一个点的时候，它作为集合的father
    // 检查完这个点，将它合并到它的父节点
    // 从ans - 1开始，依次删除，直到当前节点不断
    // 如果当前节点i不断，那么把积累重量加到父节点
    while( ropes[i].c < ropes[i].wt ) {
        --ans;
        ropes[find(ans)].wt -= ropes[ans].w;
    }
    father[i] = ropes[i].p;
    if( father[i] != -1 ) ropes[father[i]].wt += ropes[i].wt;
    return ans;
}

int main() {

    int ans, n;
    scanf( "%d", &n );
    ans = n;
    for( int i = 0; i < n; ++i ) {
        scanf( "%d%d%d", &ropes[i].c, &ropes[i].w, &ropes[i].p );
        father[i] = i;
        ropes[i].wt = ropes[i].w;
        // 如果连自己都断，那么答案肯定小于等于i
        if( ropes[i].c < ropes[i].w ) {
            ans = i;
            break;
        }
    }

    // 从更小的可能开始，依次向前检查
    for( int i = ans - 1; i >= 0; --i ) {
        ans = update( i, ans );
    }

    printf( "%d\n", ans );

    return 0;
}