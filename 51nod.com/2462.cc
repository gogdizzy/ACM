//
// Created by 关鑫 on 2020/5/14.
//
// 贪心，从左到右，如果左边的比当前的深，那么当前的就无需填充，否则只需要填充差值

#include <stdio.h>

int main() {
    int n, d, pre = 0, ans = 0;
    scanf( "%d", &n );
    for( int i = 0; i < n; ++i ) {
        scanf( "%d", &d );
        if( d > pre ) ans += d - pre;
        pre = d;
    }

    printf( "%d\n", ans );
    return 0;
}