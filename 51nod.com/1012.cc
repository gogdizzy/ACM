/**
*  http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1012
*  最小公倍数LCM
*  思路：lcm(x,y) = x / gcd(x,y) * y
*/

#include <stdio.h>
#define  ull  unsigned long long
int main() {
  int  a, b, t;
  ull  x;
  scanf( "%d%d", &a, &b );
  x = (ull) a * (ull) b;
  while( b != 0 ) {
    t = a % b;
    a = b;
    b = t;
  }
  printf( "%I64d\n", x / a );
  return 0;
}