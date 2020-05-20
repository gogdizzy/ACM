//
// Created by 关鑫 on 2020/5/14.
//

#include <algorithm>
#include <iostream>
#include <cstring>

using std::cin;
using std::cout;

#define MAXN 100001
#define MAXV 100001

int a[MAXN];
int dp[MAXV];

int main() {

    int t;

    cin >> t;
    while( t-- ) {
        int n, mx = 0, ans = 0;
        cin >> n;
        for( int i = 1; i <= n; ++i ) {
            cin >> a[i];
            if( a[i] > mx ) mx = a[i];
        }
        std::sort( a + 1, a + n + 1 );
        memset( dp, 0, sizeof(int) * (mx + 1) );
        dp[0] = 1;
        for( int i = 1; i <= n; ++i ) {
            if( dp[a[i]] ) continue;
            ++ans;
            for( int k = a[i]; k <= a[n]; ++k ) {
                dp[k] |= dp[k - a[i]];
            }
        }
        cout << ans << '\n';
    }

    return 0;
}

