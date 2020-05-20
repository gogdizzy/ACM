//
// Created by 关鑫 on 2020/5/19.
//

#include <iostream>
#include <algorithm>

using namespace std;

#define MAXN 1000

int a[MAXN];

int main() {

    ios::sync_with_stdio( false );
    cin.tie( 0 );

    int n, ans = 0;

    cin >> n;

    for( int i = 0; i < n; ++i ) {
        cin >> a[i];
    }

    sort( a, a + n );

    for( int i = 0; i < n; ++i ) {
        for( int j = i + 1, k = j + 1; j < n; ++j ) {
            auto s = a[i] + a[j];
            while( k < n && a[k] < s ) ++k;
            if( k > j ) ans += k - j - 1;
        }
    }

    cout << ans;

    return 0;
}