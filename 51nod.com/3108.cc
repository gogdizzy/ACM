//
// Created by 关鑫 on 2020/5/5.
//

#include <stdio.h>
#include <map>
#include <algorithm>

#define MAXN 100000

struct Item {
    int v;
    int r;
    int t;
};

Item items[MAXN];

int main() {
    int n, m;
    scanf( "%d%d", &n, &m );
    for( int i = 0; i < n; ++i ) {
        scanf( "%d%d%d", &items[i].v, &items[i].r, &items[i].t );
    }
    std::sort( items, items + n, [](const Item &a, const Item &b) {
        return a.r < b.r || (a.r == b.r && a.v < b.v);
    } );

    std::map< int, long long > cost;
    cost[1] = 0;
    for( int i = 0; i < n; ++i ) {
        auto it = cost.lower_bound( items[i].r );
        if( it == cost.end() ) {
            break;
        }
        auto it2 = cost.lower_bound( items[i].v );
        auto co = it->second + items[i].t;
        if( it2 != cost.end() && it2->second <= co ) continue;
        cost[items[i].v] = co;
        auto it3 = cost.find( items[i].v );
        for( --it3; it3 != cost.begin(); --it3 ) {
            if( it3->second >= co ) {
                it3 = cost.erase( it3 );
            }
        }
    }

    auto it = cost.lower_bound( m );
    if( it != cost.end() ) printf( "%lld\n", it->second );
    else puts( "-1" );

    return 0;
}