//
// Created by 关鑫 on 2020/4/29.
//

#include <stdio.h>

#define MAXN 502

char s[MAXN];
int right[256];
int ans[26];

int main() {
    int n;
    scanf( "%d%s", &n, s + 1 );
    for( int i = n; i >= 1; --i ) {
        int k = s[i];
        if( right[k] == 0 ) right[k] = i;
    }

    int m = 0;
    int pre = 0;
    int last = right[s[1]];
    for( int i = 1; last; ++i ) {
        int next = right[s[i]];
        if( i == last ) {
            ans[m++] = i - pre;
            pre = i;
            last = right[s[i + 1]];
        }
        else if( next > last ) {
            last = next;
        }
    }

    printf( "%d\n", m );
    for( int i = 0; i < m; ++i ) printf( "%d ", ans[i] );

    return 0;
}