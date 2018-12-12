/**
 * https://www.51nod.com/Challenge/Problem.html#!#problemId=1171
 * 两个数的平方和
 * 思路：http://www.cppblog.com/wujiawei/archive/2010/08/18/123784.html
 **/


#include <stdio.h>

#define LL long long

int main() {
    LL n;
    scanf( "%lld", &n );

    for( int i = 1; i * i < n; ++i ) {
        for( int k = 1; k * k < n; ++k ) {
            if( i * i + k * k == n ) printf( "%d %d\n", i, k );
        }
    }

    return 0;
}