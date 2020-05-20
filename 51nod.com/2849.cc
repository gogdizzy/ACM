//
// Created by 关鑫 on 2020/5/15.
//

#include <algorithm>
#include <iostream>
#include <cstdint>

using namespace std;

#define MAXN 200001

int a[MAXN];
int64_t v[MAXN];

int main() {

    ios::sync_with_stdio( false );
    cin.tie( 0 );

    int n, m, ans = MAXN;

    cin >> n;

    for( int i = 1; i <= n; ++i ) {
        cin >> a[i];
    }

    int64_t p = 0;
    int nxt;
    for( int i = 1; i <= n; ++i ) {
        if( v[i] ) continue;
        p += MAXN;
        v[i] = p++;
        nxt = a[i];
        while( v[nxt] == 0 ) {
            v[nxt] = p++;
            nxt = a[nxt];
        }
        auto tmp = p - v[nxt];
        if( tmp < MAXN ) {
            ans = std::min( ans, (int)tmp );
        }
    }

    cout << ans << '\n';

    return 0;
}