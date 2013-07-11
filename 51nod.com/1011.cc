/**
*  http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1011
*  最大公约数GCD
*  思路：欧几里得辗转相除
*/

#include <stdio.h>

int main() {
  int  a, b, t;
  scanf( "%d%d", &a, &b );
  while( b != 0 ) {
    t = a % b;
    a = b;
    b = t;
  }
  printf( "%d\n", a );
  return 0;
}