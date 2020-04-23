//
// Created by 关鑫 on 2020/4/23.
//

#include <iostream>
#include <string>
#include <deque>
#include <cstdint>

using std::cin;
using std::cout;
using std::string;
using std::deque;

#define MAXN 5000000

string s[MAXN];

int main() {

    std::ios::sync_with_stdio( false );
    cin.tie( 0 );

    int n;
    cin >> n;
    for( int i = 0; i < n; ++i ) cin >> s[i];

    deque<int> bucket[2][256];

    int from = 0, to = 1;
    int pos = s[0].size() - 1;
    for( int i = 0; i < n; ++i ) bucket[from][(uint8_t)s[i][pos]].push_back(i);


    for( --pos; pos >= 0; --pos ) {
        for( int c = 0; c < 256; ++c ) bucket[to][c].clear();
        for( int c = 0; c < 256; ++c ) {
            for( auto i : bucket[from][c] ) {
                bucket[to][(uint8_t)s[i][pos]].push_back(i);
            }
        }
        from = 1 - from;
        to = 1 - to;
    }

    for( int c = 0; c < 256; ++c ) {
        for( auto i : bucket[from][c] ) {
            cout << s[i] << '\n';
        }
    }

    return 0;
}

