//
// Created by 关鑫 on 2019-06-21.
//

/**
 * http://www.51nod.com/Challenge/Problem.html#!#problemId=1657
 * 电子龟
 * 思路：dp[i][j][k]表示执行到第i个命令，更改j次指令，并且朝向为k时，离起始点的最远距离
 */

#include <iostream>
#include <string>
#include <algorithm>

static constexpr size_t S = 100;
static constexpr size_t N = 50;

int dp[S][N][2];

int calc( const std::string &s, int n ) {
    return 0;
}

int main() {
    std::string s;
    int n;
    std::cin >> s >> n;
    std::cout << calc( s, n ) << '\n';
    std::lower_bound()

    return 0;
}