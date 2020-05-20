//
// Created by 关鑫 on 2020/4/28.
//

#include <stdio.h>

#define MAXN 100001

int val[MAXN];
int son[MAXN];
int sib[MAXN];
int ans[MAXN];

void dfs( int x, int depth ) {
    if( val[x] > ans[depth] ) ans[depth] = val[x];
    for( int i = son[x]; i; i = sib[i] ) dfs( i, depth + 1);
}

int main() {
    int n = 0, f;
    scanf( "%d", &n );
    for( int i = 1; i <= n; ++i ) {
        scanf( "%d %d", &f, val + i );
        if( son[f] ) {
            sib[i] = son[f];
        }
        son[f] = i;
    }
    dfs( son[0], 1 );
    for( int i = 1; i <= n && ans[i]; ++i ) printf( "%d ", ans[i] );
    return 0;
}
