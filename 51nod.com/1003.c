/**
*  http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1003
*  阶乘后面0的数量
*  思路：只需要提取因子5出现的次数就可以
*/

#include <stdio.h>

int main() {
  int  n, r = 0;
  scanf( "%d", &n );
  while( n ) {
    r += n /= 5;
  }
  printf( "%d\n", r );
  return 0;
}