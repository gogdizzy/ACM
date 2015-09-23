/*
@author gogdizzy
@date   2015-09-23

@question
        http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1002

@solution
        简单的动态规划题，可以考虑把数塔左对齐，
        设 dp[i][j] 表示走到第i行第j个数字能达到的最大值，那么递推公式就是
        dp[i][j] = max{ dp[i-1][j-1], dp[i-1][j] } + v[i][j]

        为了处理方便数组基于1，从递推式可以看出，每个数据只依赖于上一行，所以
        可以使用滚动数组，这时空间是 O(2 * N)

        又因为只依赖于当前位置上方和左上方两个数据，可以用一个变量缓存上一行
        左上方的数据，从而达到只使用 O(N) 空间
*/

#include <stdio.h>

#define MAX(a, b)  ( (a) > (b) ? (a) : (b) )
#define MAXN 500

int  dp[MAXN+1];

int main() {
         
        int  n, i, j, x, a, b;
         
        scanf( "%d", &n );
        for( i = 1; i <= n; ++i ) {
                a = 0;
                for( j = 1; j <= i; ++j ) {
                        scanf( "%d", &x );
                        b = MAX( dp[j-1], dp[j] ) + x;
                        dp[j-1] = a;
                        a = b; 
                }
                dp[i] = a;
        }

	x = dp[1];
        for( i = 2; i <= n; ++i )
                if( dp[i] > x ) x = dp[i];

        printf( "%d\n", x );

        return 0;
}
