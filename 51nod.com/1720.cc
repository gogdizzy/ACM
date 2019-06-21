//
// Created by 关鑫 on 2019-06-21.
//

/**
 * http://www.51nod.com/Challenge/Problem.html#!#problemId=1720
 * 祖玛
 * 思路：dp[i][j]表示消掉区间[i,j]需要最少的步骤
 *
 */

#include <iostream>

static constexpr size_t N = 500;

int a[N];
int dp[N][N];
int dp2[N][N];

int calc( int l, int r ) {
    if( dp[l][r] > 0 ) return dp[l][r];
    int res = N;
    if( l == r ) res = 1;
    else if( a[l] == a[r] ) {
        if( l + 1 == r ) res = 1;
        else res = calc( l + 1, r - 1 ); // 1 2 2 2 1 1 2 1 2 1，去皮的方法是不对的
    }
    for( int k = l; k < r; ++k ) {
        int tmp = calc( l, k ) + calc( k + 1, r );
        if( tmp < res ) res = tmp;
    }
    return dp[l][r] = res;
}

int main() {
    int n;
    std::cin >> n;
    for( int i = 0; i < n; ++i ) std::cin >> a[i];
    std::cout << calc( 0, n - 1 ) << '\n';

    return 0;
}