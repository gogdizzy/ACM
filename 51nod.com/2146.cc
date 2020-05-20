//
// Created by 关鑫 on 2020/5/19.
//

#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

#define MAXN 1000

int rope[MAXN];

int main() {

    ios::sync_with_stdio( false );
    cin.tie( 0 );

    int n, k;
    double x;

    cin >> n >> k;

    for( int i = 0; i < n; ++i ) {
        cin >> x;
        rope[i] = round( x * 10000 );
    }

    int l = 1, r = 100000001, m;
    while( l + 1 < r ) {
        m = ( l + r ) / 2;
        int sum = 0;
        for( int i = 0; i < n; ++i ) sum += rope[i] / m;
        if( sum >= k ) l = m;
        else r = m;
    }

    int ans = l;
    cout << ans / 10000 << '.' << setw(2) << setfill('0') << ( ans + 50 ) % 10000 / 100 << '\n';

    return 0;
}