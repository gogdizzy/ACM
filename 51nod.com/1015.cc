/**
*  http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1015
*  水仙花数
*  思路：水仙花数非常少，直接预算好，查表即可。
*/

#include <stdio.h>

int main() {
  int  m, i, a[] = { 153, 370, 371, 407, 1634 };
  scanf( "%d", &m );
  for( i = 0; ; ++i ) if( a[i] >= m ) { printf( "%d\n", a[i] ); break; }
  return 0;
}