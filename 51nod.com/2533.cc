//
// Created by 关鑫 on 2020/5/8.
//
// 先排序，从左到右扫描，如果字符相同位置相差奇数，或者字符不同位置相差偶数，则必有相同

#include <stdio.h>
#include <algorithm>

#define MAXM 51

struct Str {
    int pos;
    char val;
};
Str s[MAXM];
char tmp[MAXM];

int main() {

    int n, m;

    scanf( "%d%d", &n, &m );

    for( int i = 0; i < m; ++i ) scanf( "%d", &s[i].pos );

    scanf( "%s", tmp );
    for( int i = 0; i < m; ++i ) s[i].val = tmp[i];

    std::sort( s, s + m, [](const Str &a, const Str &b) {
        return a.pos < b.pos;
    } );

    for( int i = 0; i < m; ++i ) printf( "%d %c\n", s[i].pos, s[i].val );

    int pre = s[0].pos, cur, ans = 0;
    for( int i = 1; i < m; ++i ) {
        cur = s[i].pos;
        if( ( ( s[i].val - s[i-1].val ) ^ ( cur - pre ) ) & 1 ) ++ans;
        pre = cur;
    }

    printf( "%d\n", ans );

    return 0;
}