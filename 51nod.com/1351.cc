/**
 * https://www.51nod.com/Challenge/Problem.html#!#problemId=1351
 * 吃点心
 * 思路：最小值按从大到小取，最大值按从小到大取，要么最小值的和大于等于X，要么最大值的和刚刚小于C-X
 **/


#include <stdio.h>
#include <algorithm>
#include <functional>

#define  MAXN  50

int high[MAXN];
int low[MAXN];

int main() {

    int t, n, c, x;
    int sumlow, sumhigh, anslow, anshigh;

    for( scanf( "%d", &t ); t--; ) {
        scanf( "%d%d%d", &n, &c, &x );
        for( int i = 0; i < n; ++i ) scanf( "%d%d", low + i, high + i );

        std::sort( low, low + n, std::greater< int >() );
        std::sort( high, high + n, std::less< int >() );

        anslow = anshigh = n;
        sumlow = sumhigh = 0;
        for( int i = 0; i < n; ++i ) {
            sumlow += low[i];
            if( sumlow >= x ) {
                anslow = i + 1;
                break;
            }
        }

        for( int i = 0; i < n; ++i ) {
            sumhigh += high[i];
            if( sumhigh > c - x ) {
                anshigh = n - i;
                break;
            }
        }

        printf( "%d\n", std::min( anslow, anshigh ) );
    }
    return 0;
}
