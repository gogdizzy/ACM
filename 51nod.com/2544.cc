//
// Created by 关鑫 on 2020/5/18.
//
// 对所有点按高度排序后
// 如果一个点周围有vis过的边界点，则标记自己为边界
// 如果一个点周围有vis过的内部点，则合并到自己


#include <algorithm>
#include <iostream>

using namespace std;

typedef pair< int, int > Pii;

#define MAXN 1002

int pool[MAXN][MAXN];
Pii f[MAXN][MAXN];
Pii pos[MAXN * MAXN];
bool vis[MAXN][MAXN];
bool border[MAXN][MAXN];
Pii dir[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
int n, x = 0;

inline bool isBorder( Pii const &x ) {
    return border[x.first][x.second] || x.first <= 1 || x.first >= n || x.second <= 1 || x.second >= n;
}

Pii find( Pii const &x ) {
    Pii & fx = f[x.first][x.second];
    if( fx == x ) return x;
    return fx = find( fx );
}

void merge( Pii const &ft, Pii const &sn ) {
    Pii fft = find( ft );
    Pii fsn = find( sn );
    f[fsn.first][fsn.second] = fft;
}

int main() {

    ios::sync_with_stdio( false );
    cin.tie( 0 );

    cin >> n;

    for( int i = 1; i <= n; ++i ) {
        for( int j = 1; j <= n; ++j ) {
            cin >> pool[i][j];
            f[i][j] = { i, j };
            pos[x++] = { i, j };
        }
    }

    sort( pos, pos + x, []( Pii const &a, Pii const &b ) {
        return pool[a.first][a.second] < pool[b.first][b.second];
    } );

    for( int i = 0; i < x; ++i ) {
        Pii &p = pos[i];
        vis[p.first][p.second] = true;
        if( isBorder( p ) ) border[p.first][p.second] = true;
        for( int d = 0; d < 4; ++d ) {
            Pii nb = { p.first + dir[d].first, p.second + dir[d].second };
            if( vis[nb.first][nb.second] ) {
                Pii fnb = find( nb );
                bool nbIsBorder = isBorder( fnb );
                if( nbIsBorder ) border[p.first][p.second] = true;
                else merge( p, fnb );
            }
        }
    }

    long long ans = 0;
    for( int i = 0; i < x; ++i ) {
        Pii &p = pos[i];
        if( border[p.first][p.second] ) continue;
        Pii fp = find( p );
        ans += pool[fp.first][fp.second] - pool[p.first][p.second];
    }

    cout << ans;

    return 0;
}