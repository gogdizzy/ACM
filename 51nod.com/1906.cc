//
// Created by 关鑫 on 2020/5/19.
//

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

typedef long long LL;

#define MAXN 1000002

const int b1 = 131;
const int b2 = 1331;
const int mod = 1e9 + 7;
int h1[MAXN];
int h2[MAXN];

template < typename T >
T powmod( const T& a, const T& b, const T& p ) {
    T ans = 1, tmp = a, b0 = b;
    while( b0 != 0 ) {
        if( b0 & 1 ) ans = ans * tmp % p;
        tmp = tmp * tmp % p;
        b0 /= 2;
    }
    return ans;
}

int main() {

    ios::sync_with_stdio( false );
    cin.tie( 0 );

    int L, k;
    string s;
    unordered_set< LL > uniq;

    cin >> L >> k >> s;

    for( int i = 0; i < s.size(); ++i ) {
        h1[i + 1] = ( (LL)h1[i] * b1 + s[i] ) % mod;
        h2[i + 1] = ( (LL)h2[i] * b2 + s[i] ) % mod;
        if( i + 1 >= L ) {
            uniq.insert( LL( ( h1[i + 1] - h1[i + 1 - L] * powmod< LL >( b1, L, mod ) % mod + mod ) % mod ) << 32 |
                         LL( ( h2[i + 1] - h2[i + 1 - L] * powmod< LL >( b2, L, mod ) % mod + mod ) % mod ) );
        }
    }

    cout << uniq.size() << '\n';

    return 0;
}