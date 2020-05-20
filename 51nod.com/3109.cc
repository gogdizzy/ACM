//
// Created by 关鑫 on 2020/5/5.
//

#include <stdio.h>
#include <map>
#include <unordered_map>

#define MAXN 200002

int ming[MAXN];

int main() {
    int l, m, n, lang;
    std::map< int, int > tbl;
    scanf( "%d%d%d", &l, &m, &n );
    for( int i = 0; i < l; ++i ) {
        scanf( "%d", &lang );
        tbl[lang] = 1;
    }
    std::unordered_map< int, int > to1;
    int x = 1;
    for( auto &it : tbl ) {
        to1[it.first] = x++;
    }

    for( int i = 0; i < m; ++i ) {
        scanf( "%d", &lang );
        auto it = to1.find( lang );
        if( to1.end() == it ) continue;
        ++ming[it->second];
    }

    int a, b;
    int best = 0, better = 0;
    for( int i = 0; i < n; ++i ) {
        scanf( "%d%d", &a, &b );
        auto a1 = to1[a];
        auto b1 = to1[b];
        auto tmp1 = ming[a1 - 1] + ming[a1] + ming[a1 + 1];
        auto tmp2 = ming[b1 - 1] + ming[b1] + ming[b1 + 1];
        if( tmp1 > best || ( tmp1 == best && tmp2 > better ) ) {
            best = tmp1;
            better = tmp2;
        }
    }

    printf( "%d %d\n", best, better );

    return 0;
}