//
// Created by 关鑫 on 2020/5/4.
//


#include <stdio.h>
#include <queue>
#include <vector>

#define MAXN 5001

bool vis[MAXN];
std::vector< int > neib[MAXN];

int main() {
    int n, m, u, v;
    std::priority_queue< int, std::vector<int>, std::greater<int> > q;
    scanf( "%d%d", &n, &m );
    for( int i = 0; i < m; ++i ) {
        scanf( "%d%d", &u, &v );
        neib[u].push_back( v );
        neib[v].push_back( u );
    }

    q.push( 1 );
    while( q.size() ) {
        int cur = q.top();
        q.pop();
        printf( "%d ", cur );
        vis[cur] = true;
        for( auto nb : neib[cur] ) {
            if( !vis[nb] ) q.push( nb );
        }
    }

    return 0;
}