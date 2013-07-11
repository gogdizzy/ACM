/**
*  http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1013
*  3的幂的和 Mod 1000000007
*  思路：先用求和公式
*        f(n) = 3^0 + ... + 3^n = ( 3^(n+1) - 1 ) / ( 3 - 1 )
*        分母是2，可以知道它对1000000007的乘法逆元inv2是(1000000007 + 1)/2
*        f(n) == ( 3^(n+1) - 1 ) * inv2 (mod P)
*/

#include <stdio.h>
#define  ULL  unsigned long long
#define  P  1000000007U
#define  Inv2  ( (P+1)/2 )

int main() {
  unsigned int  n;
  ULL  mod = 1, tmp = 3ULL;
  scanf( "%u", &n ); ++n;
  while( n ) {
    if( n & 1 ) mod = mod * tmp % P;
    tmp = tmp * tmp % P;
    n >>= 1;
  }
  
  printf( "%I64u\n", ( mod + P - 1 ) * Inv2 % P );
  return 0;
}