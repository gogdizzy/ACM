/**
*  http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1004
*  n^n的末位数字
*  思路：只考虑个位数字的乘积就可以，个位数字的末尾是每4次幂循环
*/

#include <stdio.h>

int main() {
  int n, i, x, r = 1;
  scanf( "%d", &n );
  x = n % 10;
  switch( n & 3 ) {
    case 0: r *= x;
    case 3: r *= x;
    case 2: r *= x;
    case 1: r *= x;
  }
  printf( "%d\n", r % 10 );
  return 0;
}