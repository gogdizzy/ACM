/**
*  http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1008
*  NµÄ½×³Ë mod P
*  Ë¼Â·£ºÓ²Ëã
*/

#include <stdio.h>

int main() {
  unsigned int  n, p, i, j;
  unsigned long long  ans;
  scanf( "%u%u", &n, &p );
  ans = ( n & 1 ) ? n / 2 + 1 : 1;
  for( i = 1, j = n; i < j; ++i, --j ) {
    ans = i * j * ans % p;
  }
  printf( "%I64u\n", ans );
  return 0;
}