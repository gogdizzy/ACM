/**
*  http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1002
*  数塔取数问题
*  思路：从上到下，直接dp，因为每次只涉及到左上方的元素，所以用临时变量a保存新值，一维数组即可。
*  注意函数内部数组的初始化！！！
*/

#include <stdio.h>
#define  MAX(a, b)  ( (a) > (b) ? (a) : (b) )

int main() {
  int  i, j, n, x, a, b;
  int  dp[501] = {0};
  scanf( "%d %d", &n, dp + 1 );
  for( i = 2; i <= n; ++i ) {
    a = 0;
    for( j = 1; j <= i; ++j ) {
      scanf( "%d", &x );
      b = MAX( dp[j-1], dp[j] ) + x;
      dp[j-1] = a;
      a = b;
    }
    dp[i] = a;
  }
  for( i = 2, x = dp[1]; i <= n; ++i ) if( dp[i] > x ) x = dp[i];
  printf( "%d\n", x );
  return 0;
}